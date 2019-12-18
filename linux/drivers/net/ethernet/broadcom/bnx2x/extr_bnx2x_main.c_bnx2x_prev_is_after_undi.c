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
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DEV_INFO (char*) ; 
 int /*<<< orphan*/  DORQ_REG_NORM_CID_OFST ; 
 int MISC_REGISTERS_RESET_REG_1_RST_DORQ ; 
 int /*<<< orphan*/  MISC_REG_RESET_REG_1 ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bnx2x_prev_is_after_undi(struct bnx2x *bp)
{
	/* UNDI marks its presence in DORQ -
	 * it initializes CID offset for normal bell to 0x7
	 */
	if (!(REG_RD(bp, MISC_REG_RESET_REG_1) &
	    MISC_REGISTERS_RESET_REG_1_RST_DORQ))
		return false;

	if (REG_RD(bp, DORQ_REG_NORM_CID_OFST) == 0x7) {
		BNX2X_DEV_INFO("UNDI previously loaded\n");
		return true;
	}

	return false;
}