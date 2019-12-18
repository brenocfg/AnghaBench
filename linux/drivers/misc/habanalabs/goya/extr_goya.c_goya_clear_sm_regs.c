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
struct hl_device {int dummy; } ;

/* Variables and functions */
 int RREG32 (int) ; 
 int /*<<< orphan*/  WREG32 (int,int /*<<< orphan*/ ) ; 
 int mmSYNC_MNGR_MON_STATUS_0 ; 
 int mmSYNC_MNGR_MON_STATUS_255 ; 
 int mmSYNC_MNGR_SOB_OBJ_0 ; 
 int mmSYNC_MNGR_SOB_OBJ_1023 ; 

__attribute__((used)) static void goya_clear_sm_regs(struct hl_device *hdev)
{
	int i, num_of_sob_in_longs, num_of_mon_in_longs;

	num_of_sob_in_longs =
		((mmSYNC_MNGR_SOB_OBJ_1023 - mmSYNC_MNGR_SOB_OBJ_0) + 4);

	num_of_mon_in_longs =
		((mmSYNC_MNGR_MON_STATUS_255 - mmSYNC_MNGR_MON_STATUS_0) + 4);

	for (i = 0 ; i < num_of_sob_in_longs ; i += 4)
		WREG32(mmSYNC_MNGR_SOB_OBJ_0 + i, 0);

	for (i = 0 ; i < num_of_mon_in_longs ; i += 4)
		WREG32(mmSYNC_MNGR_MON_STATUS_0 + i, 0);

	/* Flush all WREG to prevent race */
	i = RREG32(mmSYNC_MNGR_SOB_OBJ_0);
}