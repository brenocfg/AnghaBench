#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  (* faa_cbfn ) (void*,int /*<<< orphan*/ ) ;void* faa_cbarg; } ;
struct TYPE_7__ {int /*<<< orphan*/  busy; TYPE_3__ faa_cb; TYPE_1__* faa_attr; } ;
struct bfa_iocfc_s {TYPE_2__ faa_args; } ;
struct TYPE_9__ {int /*<<< orphan*/  addr_source; int /*<<< orphan*/  faa_status; int /*<<< orphan*/  faa; } ;
typedef  TYPE_4__ bfi_faa_query_rsp_t ;
struct TYPE_6__ {int /*<<< orphan*/  pwwn_source; int /*<<< orphan*/  faa_state; int /*<<< orphan*/  faa; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_STATUS_OK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_faa_query_reply(struct bfa_iocfc_s *iocfc,
		bfi_faa_query_rsp_t *rsp)
{
	void	*cbarg = iocfc->faa_args.faa_cb.faa_cbarg;

	if (iocfc->faa_args.faa_attr) {
		iocfc->faa_args.faa_attr->faa = rsp->faa;
		iocfc->faa_args.faa_attr->faa_state = rsp->faa_status;
		iocfc->faa_args.faa_attr->pwwn_source = rsp->addr_source;
	}

	WARN_ON(!iocfc->faa_args.faa_cb.faa_cbfn);

	iocfc->faa_args.faa_cb.faa_cbfn(cbarg, BFA_STATUS_OK);
	iocfc->faa_args.busy = BFA_FALSE;
}