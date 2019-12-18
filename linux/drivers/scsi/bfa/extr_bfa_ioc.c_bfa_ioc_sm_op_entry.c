#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bfad_s {int dummy; } ;
struct bfa_ioc_s {TYPE_2__* bfa; TYPE_1__* cbfn; } ;
struct TYPE_4__ {scalar_t__ bfad; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* enable_cbfn ) (TYPE_2__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_IOC_AEN_ENABLE ; 
 int /*<<< orphan*/  BFA_IOC_E_ENABLED ; 
 int /*<<< orphan*/  BFA_LOG (int /*<<< orphan*/ ,struct bfad_s*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  bfa_ioc_aen_post (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_event_notify (struct bfa_ioc_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_ioc_hb_monitor (struct bfa_ioc_s*) ; 
 int /*<<< orphan*/  bfa_log_level ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_ioc_sm_op_entry(struct bfa_ioc_s *ioc)
{
	struct bfad_s *bfad = (struct bfad_s *)ioc->bfa->bfad;

	ioc->cbfn->enable_cbfn(ioc->bfa, BFA_STATUS_OK);
	bfa_ioc_event_notify(ioc, BFA_IOC_E_ENABLED);
	bfa_ioc_hb_monitor(ioc);
	BFA_LOG(KERN_INFO, bfad, bfa_log_level, "IOC enabled\n");
	bfa_ioc_aen_post(ioc, BFA_IOC_AEN_ENABLE);
}