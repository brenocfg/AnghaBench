#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct esas2r_adapter {TYPE_1__* pcid; int /*<<< orphan*/  flags2; int /*<<< orphan*/  fw_coredump_buff; } ;
struct TYPE_2__ {scalar_t__ revision; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF2_COREDUMP_AVAIL ; 
 int /*<<< orphan*/  AF2_COREDUMP_SAVED ; 
 int /*<<< orphan*/  ESAS2R_FWCOREDUMP_SZ ; 
 int /*<<< orphan*/  MU_CTL_IN_FULL_RST ; 
 int /*<<< orphan*/  MU_CTL_IN_FULL_RST2 ; 
 int /*<<< orphan*/  MU_CTL_STATUS_IN ; 
 int /*<<< orphan*/  MU_CTL_STATUS_IN_B2 ; 
 scalar_t__ MVR_FREY_B2 ; 
 scalar_t__ MW_DATA_ADDR_SRAM ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_is_adapter_present (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_read_mem_block (struct esas2r_adapter*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_write_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void esas2r_reset_chip(struct esas2r_adapter *a)
{
	if (!esas2r_is_adapter_present(a))
		return;

	/*
	 * Before we reset the chip, save off the VDA core dump.  The VDA core
	 * dump is located in the upper 512KB of the onchip SRAM.  Make sure
	 * to not overwrite a previous crash that was saved.
	 */
	if (test_bit(AF2_COREDUMP_AVAIL, &a->flags2) &&
	    !test_bit(AF2_COREDUMP_SAVED, &a->flags2)) {
		esas2r_read_mem_block(a,
				      a->fw_coredump_buff,
				      MW_DATA_ADDR_SRAM + 0x80000,
				      ESAS2R_FWCOREDUMP_SZ);

		set_bit(AF2_COREDUMP_SAVED, &a->flags2);
	}

	clear_bit(AF2_COREDUMP_AVAIL, &a->flags2);

	/* Reset the chip */
	if (a->pcid->revision == MVR_FREY_B2)
		esas2r_write_register_dword(a, MU_CTL_STATUS_IN_B2,
					    MU_CTL_IN_FULL_RST2);
	else
		esas2r_write_register_dword(a, MU_CTL_STATUS_IN,
					    MU_CTL_IN_FULL_RST);


	/* Stall a little while to let the reset condition clear */
	mdelay(10);
}