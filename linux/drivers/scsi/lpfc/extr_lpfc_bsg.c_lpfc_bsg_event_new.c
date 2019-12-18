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
typedef  void* uint32_t ;
struct lpfc_bsg_event {int reg_id; int /*<<< orphan*/  kref; int /*<<< orphan*/  wq; int /*<<< orphan*/ * dd_data; int /*<<< orphan*/  wait_time_stamp; void* req_id; void* type_mask; int /*<<< orphan*/  events_to_see; int /*<<< orphan*/  events_to_get; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct lpfc_bsg_event* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct lpfc_bsg_event *
lpfc_bsg_event_new(uint32_t ev_mask, int ev_reg_id, uint32_t ev_req_id)
{
	struct lpfc_bsg_event *evt = kzalloc(sizeof(*evt), GFP_KERNEL);

	if (!evt)
		return NULL;

	INIT_LIST_HEAD(&evt->events_to_get);
	INIT_LIST_HEAD(&evt->events_to_see);
	evt->type_mask = ev_mask;
	evt->req_id = ev_req_id;
	evt->reg_id = ev_reg_id;
	evt->wait_time_stamp = jiffies;
	evt->dd_data = NULL;
	init_waitqueue_head(&evt->wq);
	kref_init(&evt->kref);
	return evt;
}