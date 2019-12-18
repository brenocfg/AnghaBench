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
struct adapter {TYPE_1__* uld; } ;
typedef  enum cxgb4_uld { ____Placeholder_cxgb4_uld } cxgb4_uld ;
typedef  enum cxgb4_control { ____Placeholder_cxgb4_control } cxgb4_control ;
struct TYPE_2__ {scalar_t__ handle; int /*<<< orphan*/  (* control ) (scalar_t__,int) ;} ;

/* Variables and functions */
 int CXGB4_ULD_RDMA ; 
 int /*<<< orphan*/  stub1 (scalar_t__,int) ; 

__attribute__((used)) static void notify_rdma_uld(struct adapter *adap, enum cxgb4_control cmd)
{
	enum cxgb4_uld type = CXGB4_ULD_RDMA;

	if (adap->uld && adap->uld[type].handle)
		adap->uld[type].control(adap->uld[type].handle, cmd);
}