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
struct bfa_cee_attr {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  get_attr_cbarg; int /*<<< orphan*/  (* get_attr_cbfn ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  kva; } ;
struct bfa_cee {int get_attr_status; int get_attr_pending; TYPE_2__ cbfn; int /*<<< orphan*/  attr; TYPE_1__ attr_dma; } ;
typedef  enum bfa_status { ____Placeholder_bfa_status } bfa_status ;

/* Variables and functions */
 int BFA_STATUS_OK ; 
 int /*<<< orphan*/  bfa_cee_format_cee_cfg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bfa_cee_get_attr_isr(struct bfa_cee *cee, enum bfa_status status)
{
	cee->get_attr_status = status;
	if (status == BFA_STATUS_OK) {
		memcpy(cee->attr, cee->attr_dma.kva,
		    sizeof(struct bfa_cee_attr));
		bfa_cee_format_cee_cfg(cee->attr);
	}
	cee->get_attr_pending = false;
	if (cee->cbfn.get_attr_cbfn)
		cee->cbfn.get_attr_cbfn(cee->cbfn.get_attr_cbarg, status);
}