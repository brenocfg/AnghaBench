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
struct v10_compute_mqd {int /*<<< orphan*/  cp_hqd_vmid; } ;
struct queue_properties {int /*<<< orphan*/  vmid; } ;
struct mqd_manager {int dummy; } ;

/* Variables and functions */
 struct v10_compute_mqd* get_mqd (void*) ; 
 int /*<<< orphan*/  update_mqd (struct mqd_manager*,void*,struct queue_properties*) ; 

__attribute__((used)) static void update_mqd_hiq(struct mqd_manager *mm, void *mqd,
			struct queue_properties *q)
{
	struct v10_compute_mqd *m;

	update_mqd(mm, mqd, q);

	/* TODO: what's the point? update_mqd already does this. */
	m = get_mqd(mqd);
	m->cp_hqd_vmid = q->vmid;
}