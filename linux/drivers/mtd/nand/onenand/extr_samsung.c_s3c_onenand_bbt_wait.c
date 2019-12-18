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
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECC_ERR_STAT_OFFSET ; 
 unsigned int INT_ACT ; 
 int /*<<< orphan*/  INT_ERR_ACK_OFFSET ; 
 int /*<<< orphan*/  INT_ERR_STAT_OFFSET ; 
 unsigned int LD_FAIL_ECC_ERR ; 
 unsigned int LOAD_CMP ; 
 int ONENAND_BBT_READ_ERROR ; 
 int ONENAND_ECC_4BIT_UNCORRECTABLE ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  s3c_onenand_reset () ; 
 void* s3c_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_write_reg (unsigned int,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int s3c_onenand_bbt_wait(struct mtd_info *mtd, int state)
{
	unsigned int flags = INT_ACT | LOAD_CMP;
	unsigned int stat;
	unsigned long timeout;

	/* The 20 msec is enough */
	timeout = jiffies + msecs_to_jiffies(20);
	while (time_before(jiffies, timeout)) {
		stat = s3c_read_reg(INT_ERR_STAT_OFFSET);
		if (stat & flags)
			break;
	}
	/* To get correct interrupt status in timeout case */
	stat = s3c_read_reg(INT_ERR_STAT_OFFSET);
	s3c_write_reg(stat, INT_ERR_ACK_OFFSET);

	if (stat & LD_FAIL_ECC_ERR) {
		s3c_onenand_reset();
		return ONENAND_BBT_READ_ERROR;
	}

	if (stat & LOAD_CMP) {
		int ecc = s3c_read_reg(ECC_ERR_STAT_OFFSET);
		if (ecc & ONENAND_ECC_4BIT_UNCORRECTABLE) {
			s3c_onenand_reset();
			return ONENAND_BBT_READ_ERROR;
		}
	}

	return 0;
}