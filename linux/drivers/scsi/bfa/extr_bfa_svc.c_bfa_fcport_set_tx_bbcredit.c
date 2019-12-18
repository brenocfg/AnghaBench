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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u16 ;
struct bfa_s {int dummy; } ;
struct TYPE_2__ {scalar_t__ tx_bbcredit; } ;
struct bfa_fcport_s {TYPE_1__ cfg; } ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (struct bfa_s*) ; 

void
bfa_fcport_set_tx_bbcredit(struct bfa_s *bfa, u16 tx_bbcredit)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	fcport->cfg.tx_bbcredit = (u8)tx_bbcredit;
}