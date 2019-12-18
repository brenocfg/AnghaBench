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

/* Variables and functions */
 int /*<<< orphan*/  ECC_ERR_STAT_OFFSET ; 
 int /*<<< orphan*/  INT_ERR_ACK_OFFSET ; 
 int /*<<< orphan*/  INT_ERR_STAT_OFFSET ; 
 int /*<<< orphan*/  MEM_RESET_OFFSET ; 
 int ONENAND_MEM_RESET_COLD ; 
 int RST_CMP ; 
 int s3c_read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s3c_write_reg (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s3c_onenand_reset(void)
{
	unsigned long timeout = 0x10000;
	int stat;

	s3c_write_reg(ONENAND_MEM_RESET_COLD, MEM_RESET_OFFSET);
	while (1 && timeout--) {
		stat = s3c_read_reg(INT_ERR_STAT_OFFSET);
		if (stat & RST_CMP)
			break;
	}
	stat = s3c_read_reg(INT_ERR_STAT_OFFSET);
	s3c_write_reg(stat, INT_ERR_ACK_OFFSET);

	/* Clear interrupt */
	s3c_write_reg(0x0, INT_ERR_ACK_OFFSET);
	/* Clear the ECC status */
	s3c_write_reg(0x0, ECC_ERR_STAT_OFFSET);
}