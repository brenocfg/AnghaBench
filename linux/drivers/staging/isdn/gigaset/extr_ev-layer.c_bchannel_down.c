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
struct bc_state {int chstate; } ;

/* Variables and functions */
 int CHS_B_UP ; 
 int CHS_D_UP ; 
 int CHS_NOTIFY_LL ; 
 int /*<<< orphan*/  gigaset_bcs_reinit (struct bc_state*) ; 
 int /*<<< orphan*/  gigaset_free_channel (struct bc_state*) ; 
 int /*<<< orphan*/  gigaset_isdn_hupB (struct bc_state*) ; 
 int /*<<< orphan*/  gigaset_isdn_hupD (struct bc_state*) ; 

__attribute__((used)) static void bchannel_down(struct bc_state *bcs)
{
	if (bcs->chstate & CHS_B_UP) {
		bcs->chstate &= ~CHS_B_UP;
		gigaset_isdn_hupB(bcs);
	}

	if (bcs->chstate & (CHS_D_UP | CHS_NOTIFY_LL)) {
		bcs->chstate &= ~(CHS_D_UP | CHS_NOTIFY_LL);
		gigaset_isdn_hupD(bcs);
	}

	gigaset_free_channel(bcs);

	gigaset_bcs_reinit(bcs);
}