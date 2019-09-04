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
typedef  int uint32_t ;
struct iproc_rng200_dev {scalar_t__ base; } ;
struct hwrng {int dummy; } ;

/* Variables and functions */
 int HZ ; 
 scalar_t__ RNG_FIFO_COUNT_OFFSET ; 
 int RNG_FIFO_COUNT_RNG_FIFO_COUNT_MASK ; 
 scalar_t__ RNG_FIFO_DATA_OFFSET ; 
 int RNG_INT_STATUS_MASTER_FAIL_LOCKOUT_IRQ_MASK ; 
 int RNG_INT_STATUS_NIST_FAIL_IRQ_MASK ; 
 scalar_t__ RNG_INT_STATUS_OFFSET ; 
 int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iproc_rng200_restart (scalar_t__) ; 
 int jiffies ; 
 int /*<<< orphan*/  memcpy (void*,int*,int) ; 
 int /*<<< orphan*/  min (int,unsigned int) ; 
 scalar_t__ time_before (int,unsigned long) ; 
 struct iproc_rng200_dev* to_rng_priv (struct hwrng*) ; 
 int /*<<< orphan*/  usleep_range (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int iproc_rng200_read(struct hwrng *rng, void *buf, size_t max,
			     bool wait)
{
	struct iproc_rng200_dev *priv = to_rng_priv(rng);
	uint32_t num_remaining = max;
	uint32_t status;

	#define MAX_RESETS_PER_READ	1
	uint32_t num_resets = 0;

	#define MAX_IDLE_TIME	(1 * HZ)
	unsigned long idle_endtime = jiffies + MAX_IDLE_TIME;

	while ((num_remaining > 0) && time_before(jiffies, idle_endtime)) {

		/* Is RNG sane? If not, reset it. */
		status = ioread32(priv->base + RNG_INT_STATUS_OFFSET);
		if ((status & (RNG_INT_STATUS_MASTER_FAIL_LOCKOUT_IRQ_MASK |
			RNG_INT_STATUS_NIST_FAIL_IRQ_MASK)) != 0) {

			if (num_resets >= MAX_RESETS_PER_READ)
				return max - num_remaining;

			iproc_rng200_restart(priv->base);
			num_resets++;
		}

		/* Are there any random numbers available? */
		if ((ioread32(priv->base + RNG_FIFO_COUNT_OFFSET) &
				RNG_FIFO_COUNT_RNG_FIFO_COUNT_MASK) > 0) {

			if (num_remaining >= sizeof(uint32_t)) {
				/* Buffer has room to store entire word */
				*(uint32_t *)buf = ioread32(priv->base +
							RNG_FIFO_DATA_OFFSET);
				buf += sizeof(uint32_t);
				num_remaining -= sizeof(uint32_t);
			} else {
				/* Buffer can only store partial word */
				uint32_t rnd_number = ioread32(priv->base +
							RNG_FIFO_DATA_OFFSET);
				memcpy(buf, &rnd_number, num_remaining);
				buf += num_remaining;
				num_remaining = 0;
			}

			/* Reset the IDLE timeout */
			idle_endtime = jiffies + MAX_IDLE_TIME;
		} else {
			if (!wait)
				/* Cannot wait, return immediately */
				return max - num_remaining;

			/* Can wait, give others chance to run */
			usleep_range(min(num_remaining * 10, 500U), 500);
		}
	}

	return max - num_remaining;
}