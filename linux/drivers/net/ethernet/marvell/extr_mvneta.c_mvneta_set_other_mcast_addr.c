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
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 scalar_t__ MVNETA_DA_FILT_OTH_MCAST ; 
 unsigned int mvreg_read (struct mvneta_port*,scalar_t__) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,scalar_t__,unsigned int) ; 

__attribute__((used)) static void mvneta_set_other_mcast_addr(struct mvneta_port *pp,
					unsigned char crc8,
					int queue)
{
	unsigned int omc_table_reg;
	unsigned int tbl_offset;
	unsigned int reg_offset;

	tbl_offset = (crc8 / 4) * 4; /* Register offset from OMC table base */
	reg_offset = crc8 % 4;	     /* Entry offset within the above reg   */

	omc_table_reg = mvreg_read(pp, MVNETA_DA_FILT_OTH_MCAST + tbl_offset);

	if (queue == -1) {
		/* Clear accepts frame bit at specified Other DA table entry */
		omc_table_reg &= ~(0xff << (8 * reg_offset));
	} else {
		omc_table_reg &= ~(0xff << (8 * reg_offset));
		omc_table_reg |= ((0x01 | (queue << 1)) << (8 * reg_offset));
	}

	mvreg_write(pp, MVNETA_DA_FILT_OTH_MCAST + tbl_offset, omc_table_reg);
}