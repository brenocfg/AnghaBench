#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct s3c24xx_i2c {int /*<<< orphan*/  dev; scalar_t__ regs; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int S3C2410_IDLE_TIMEOUT ; 
 scalar_t__ S3C2410_IICSTAT ; 
 unsigned long S3C2410_IICSTAT_START ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int ktime_us_delta (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (unsigned long,int) ; 

__attribute__((used)) static void s3c24xx_i2c_wait_idle(struct s3c24xx_i2c *i2c)
{
	unsigned long iicstat;
	ktime_t start, now;
	unsigned long delay;
	int spins;

	/* ensure the stop has been through the bus */

	dev_dbg(i2c->dev, "waiting for bus idle\n");

	start = now = ktime_get();

	/*
	 * Most of the time, the bus is already idle within a few usec of the
	 * end of a transaction.  However, really slow i2c devices can stretch
	 * the clock, delaying STOP generation.
	 *
	 * On slower SoCs this typically happens within a very small number of
	 * instructions so busy wait briefly to avoid scheduling overhead.
	 */
	spins = 3;
	iicstat = readl(i2c->regs + S3C2410_IICSTAT);
	while ((iicstat & S3C2410_IICSTAT_START) && --spins) {
		cpu_relax();
		iicstat = readl(i2c->regs + S3C2410_IICSTAT);
	}

	/*
	 * If we do get an appreciable delay as a compromise between idle
	 * detection latency for the normal, fast case, and system load in the
	 * slow device case, use an exponential back off in the polling loop,
	 * up to 1/10th of the total timeout, then continue to poll at a
	 * constant rate up to the timeout.
	 */
	delay = 1;
	while ((iicstat & S3C2410_IICSTAT_START) &&
	       ktime_us_delta(now, start) < S3C2410_IDLE_TIMEOUT) {
		usleep_range(delay, 2 * delay);
		if (delay < S3C2410_IDLE_TIMEOUT / 10)
			delay <<= 1;
		now = ktime_get();
		iicstat = readl(i2c->regs + S3C2410_IICSTAT);
	}

	if (iicstat & S3C2410_IICSTAT_START)
		dev_warn(i2c->dev, "timeout waiting for bus idle\n");
}