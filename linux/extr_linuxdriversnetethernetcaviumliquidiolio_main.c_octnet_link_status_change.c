#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct work_struct {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mtu; } ;
struct TYPE_5__ {TYPE_1__ s; } ;
struct TYPE_6__ {TYPE_2__ link; } ;
struct lio {TYPE_3__ linfo; int /*<<< orphan*/  netdev; } ;
struct cavium_wk {scalar_t__ ctxptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_mtu (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void octnet_link_status_change(struct work_struct *work)
{
	struct cavium_wk *wk = (struct cavium_wk *)work;
	struct lio *lio = (struct lio *)wk->ctxptr;

	/* lio->linfo.link.s.mtu always contains max MTU of the lio interface.
	 * this API is invoked only when new max-MTU of the interface is
	 * less than current MTU.
	 */
	rtnl_lock();
	dev_set_mtu(lio->netdev, lio->linfo.link.s.mtu);
	rtnl_unlock();
}