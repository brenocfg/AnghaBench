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
struct fcoe_task_params {int /*<<< orphan*/  itid; TYPE_1__* sqe; } ;
typedef  enum fcoe_sqe_request_type { ____Placeholder_fcoe_sqe_request_type } fcoe_sqe_request_type ;
struct TYPE_2__ {int /*<<< orphan*/  task_id; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCOE_WQE_REQ_TYPE ; 
 int /*<<< orphan*/  SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void init_common_sqe(struct fcoe_task_params *task_params,
				   enum fcoe_sqe_request_type request_type)
{
	memset(task_params->sqe, 0, sizeof(*(task_params->sqe)));
	SET_FIELD(task_params->sqe->flags, FCOE_WQE_REQ_TYPE,
		  request_type);
	task_params->sqe->task_id = task_params->itid;
}