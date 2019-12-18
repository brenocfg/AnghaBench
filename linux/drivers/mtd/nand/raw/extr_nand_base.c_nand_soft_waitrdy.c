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
typedef  int u8 ;
struct nand_sdr_timings {int /*<<< orphan*/  tWB_max; } ;
struct nand_chip {int /*<<< orphan*/  data_interface; } ;
typedef  int /*<<< orphan*/  status ;

/* Variables and functions */
 int ENOTSUPP ; 
 int ETIMEDOUT ; 
 int NAND_STATUS_READY ; 
 int /*<<< orphan*/  PSEC_TO_NSEC (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  nand_exit_status_op (struct nand_chip*) ; 
 struct nand_sdr_timings* nand_get_sdr_timings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nand_has_exec_op (struct nand_chip*) ; 
 int nand_read_data_op (struct nand_chip*,int*,int,int) ; 
 int nand_status_op (struct nand_chip*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndelay (int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

int nand_soft_waitrdy(struct nand_chip *chip, unsigned long timeout_ms)
{
	const struct nand_sdr_timings *timings;
	u8 status = 0;
	int ret;

	if (!nand_has_exec_op(chip))
		return -ENOTSUPP;

	/* Wait tWB before polling the STATUS reg. */
	timings = nand_get_sdr_timings(&chip->data_interface);
	ndelay(PSEC_TO_NSEC(timings->tWB_max));

	ret = nand_status_op(chip, NULL);
	if (ret)
		return ret;

	timeout_ms = jiffies + msecs_to_jiffies(timeout_ms);
	do {
		ret = nand_read_data_op(chip, &status, sizeof(status), true);
		if (ret)
			break;

		if (status & NAND_STATUS_READY)
			break;

		/*
		 * Typical lowest execution time for a tR on most NANDs is 10us,
		 * use this as polling delay before doing something smarter (ie.
		 * deriving a delay from the timeout value, timeout_ms/ratio).
		 */
		udelay(10);
	} while	(time_before(jiffies, timeout_ms));

	/*
	 * We have to exit READ_STATUS mode in order to read real data on the
	 * bus in case the WAITRDY instruction is preceding a DATA_IN
	 * instruction.
	 */
	nand_exit_status_op(chip);

	if (ret)
		return ret;

	return status & NAND_STATUS_READY ? 0 : -ETIMEDOUT;
}