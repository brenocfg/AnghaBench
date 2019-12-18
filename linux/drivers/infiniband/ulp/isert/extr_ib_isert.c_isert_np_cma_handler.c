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
struct isert_np {int /*<<< orphan*/ * cm_id; } ;
typedef  enum rdma_cm_event_type { ____Placeholder_rdma_cm_event_type } rdma_cm_event_type ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
#define  RDMA_CM_EVENT_ADDR_CHANGE 129 
#define  RDMA_CM_EVENT_DEVICE_REMOVAL 128 
 int /*<<< orphan*/  isert_dbg (char*,int /*<<< orphan*/ ,int,struct isert_np*) ; 
 int /*<<< orphan*/  isert_err (char*,struct isert_np*,int) ; 
 int /*<<< orphan*/ * isert_setup_id (struct isert_np*) ; 
 int /*<<< orphan*/  rdma_event_msg (int) ; 

__attribute__((used)) static int
isert_np_cma_handler(struct isert_np *isert_np,
		     enum rdma_cm_event_type event)
{
	isert_dbg("%s (%d): isert np %p\n",
		  rdma_event_msg(event), event, isert_np);

	switch (event) {
	case RDMA_CM_EVENT_DEVICE_REMOVAL:
		isert_np->cm_id = NULL;
		break;
	case RDMA_CM_EVENT_ADDR_CHANGE:
		isert_np->cm_id = isert_setup_id(isert_np);
		if (IS_ERR(isert_np->cm_id)) {
			isert_err("isert np %p setup id failed: %ld\n",
				  isert_np, PTR_ERR(isert_np->cm_id));
			isert_np->cm_id = NULL;
		}
		break;
	default:
		isert_err("isert np %p Unexpected event %d\n",
			  isert_np, event);
	}

	return -1;
}