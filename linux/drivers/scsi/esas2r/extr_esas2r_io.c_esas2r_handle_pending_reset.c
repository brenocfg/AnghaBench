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
typedef  scalar_t__ u32 ;
struct esas2r_adapter {scalar_t__ chip_init_time; int max_vdareq_size; int /*<<< orphan*/  build_sgl; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_CHPRST_DETECTED ; 
 int /*<<< orphan*/  AF_LEGACY_SGE_MODE ; 
 scalar_t__ DRBL_FORCE_INT ; 
 scalar_t__ DRBL_FW_VER_0 ; 
 scalar_t__ DRBL_FW_VER_1 ; 
 scalar_t__ DRBL_FW_VER_MSK ; 
 scalar_t__ ESAS2R_CHPRST_TIME ; 
 scalar_t__ ESAS2R_CHPRST_WAIT_TIME ; 
 int /*<<< orphan*/  MU_DOORBELL_OUT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  esas2r_build_sg_list_prd ; 
 int /*<<< orphan*/  esas2r_build_sg_list_sge ; 
 int /*<<< orphan*/  esas2r_force_interrupt (struct esas2r_adapter*) ; 
 int /*<<< orphan*/  esas2r_local_reset_adapter (struct esas2r_adapter*) ; 
 scalar_t__ esas2r_read_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  esas2r_write_register_dword (struct esas2r_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void esas2r_handle_pending_reset(struct esas2r_adapter *a, u32 currtime)
{
	u32 delta = currtime - a->chip_init_time;

	if (delta <= ESAS2R_CHPRST_WAIT_TIME) {
		/* Wait before accessing registers */
	} else if (delta >= ESAS2R_CHPRST_TIME) {
		/*
		 * The last reset failed so try again. Reset
		 * processing will give up after three tries.
		 */
		esas2r_local_reset_adapter(a);
	} else {
		/* We can now see if the firmware is ready */
		u32 doorbell;

		doorbell = esas2r_read_register_dword(a, MU_DOORBELL_OUT);
		if (doorbell == 0xFFFFFFFF || !(doorbell & DRBL_FORCE_INT)) {
			esas2r_force_interrupt(a);
		} else {
			u32 ver = (doorbell & DRBL_FW_VER_MSK);

			/* Driver supports API version 0 and 1 */
			esas2r_write_register_dword(a, MU_DOORBELL_OUT,
						    doorbell);
			if (ver == DRBL_FW_VER_0) {
				set_bit(AF_CHPRST_DETECTED, &a->flags);
				set_bit(AF_LEGACY_SGE_MODE, &a->flags);

				a->max_vdareq_size = 128;
				a->build_sgl = esas2r_build_sg_list_sge;
			} else if (ver == DRBL_FW_VER_1) {
				set_bit(AF_CHPRST_DETECTED, &a->flags);
				clear_bit(AF_LEGACY_SGE_MODE, &a->flags);

				a->max_vdareq_size = 1024;
				a->build_sgl = esas2r_build_sg_list_prd;
			} else {
				esas2r_local_reset_adapter(a);
			}
		}
	}
}