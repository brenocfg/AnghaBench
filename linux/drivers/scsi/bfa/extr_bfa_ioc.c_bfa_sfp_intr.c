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
struct TYPE_2__ {int msg_id; } ;
struct bfi_mbmsg_s {TYPE_1__ mh; } ;
struct bfa_sfp_s {int dummy; } ;

/* Variables and functions */
#define  BFI_SFP_I2H_SCN 129 
#define  BFI_SFP_I2H_SHOW 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_sfp_scn (struct bfa_sfp_s*,struct bfi_mbmsg_s*) ; 
 int /*<<< orphan*/  bfa_sfp_show_comp (struct bfa_sfp_s*,struct bfi_mbmsg_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_sfp_s*,int) ; 

void
bfa_sfp_intr(void *sfparg, struct bfi_mbmsg_s *msg)
{
	struct bfa_sfp_s *sfp = sfparg;

	switch (msg->mh.msg_id) {
	case BFI_SFP_I2H_SHOW:
		bfa_sfp_show_comp(sfp, msg);
		break;

	case BFI_SFP_I2H_SCN:
		bfa_sfp_scn(sfp, msg);
		break;

	default:
		bfa_trc(sfp, msg->mh.msg_id);
		WARN_ON(1);
	}
}