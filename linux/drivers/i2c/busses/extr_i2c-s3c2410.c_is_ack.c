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

/* Variables and functions */
 scalar_t__ S3C2410_IICCON ; 
 int S3C2410_IICCON_IRQPEND ; 
 scalar_t__ S3C2410_IICSTAT ; 
 int S3C2410_IICSTAT_LASTBIT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static bool is_ack(struct s3c24xx_i2c *i2c)
{
	int tries;

	for (tries = 50; tries; --tries) {
		if (readl(i2c->regs + S3C2410_IICCON)
			& S3C2410_IICCON_IRQPEND) {
			if (!(readl(i2c->regs + S3C2410_IICSTAT)
				& S3C2410_IICSTAT_LASTBIT))
				return true;
		}
		usleep_range(1000, 2000);
	}
	dev_err(i2c->dev, "ack was not received\n");
	return false;
}