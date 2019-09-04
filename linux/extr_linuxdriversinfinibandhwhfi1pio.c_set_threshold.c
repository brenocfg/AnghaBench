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
typedef  int /*<<< orphan*/  u32 ;
struct hfi1_devdata {int /*<<< orphan*/ * kernel_send_context; TYPE_2__** rcd; TYPE_1__* vld; } ;
struct TYPE_4__ {int /*<<< orphan*/  rcvhdrqentsize; } ;
struct TYPE_3__ {int /*<<< orphan*/  mtu; } ;

/* Variables and functions */
 int /*<<< orphan*/  min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_mtu_to_threshold (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_percent_to_threshold (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sc_set_cr_threshold (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_threshold(struct hfi1_devdata *dd, int scontext, int i)
{
	u32 thres;

	thres = min(sc_percent_to_threshold(dd->kernel_send_context[scontext],
					    50),
		    sc_mtu_to_threshold(dd->kernel_send_context[scontext],
					dd->vld[i].mtu,
					dd->rcd[0]->rcvhdrqentsize));
	sc_set_cr_threshold(dd->kernel_send_context[scontext], thres);
}