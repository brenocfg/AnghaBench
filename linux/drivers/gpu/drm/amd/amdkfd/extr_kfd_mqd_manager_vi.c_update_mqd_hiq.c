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
struct vi_mqd {int /*<<< orphan*/  cp_hqd_vmid; } ;
struct queue_properties {int /*<<< orphan*/  vmid; } ;
struct mqd_manager {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTYPE_UC ; 
 int /*<<< orphan*/  __update_mqd (struct mqd_manager*,void*,struct queue_properties*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vi_mqd* get_mqd (void*) ; 

__attribute__((used)) static void update_mqd_hiq(struct mqd_manager *mm, void *mqd,
			struct queue_properties *q)
{
	struct vi_mqd *m;
	__update_mqd(mm, mqd, q, MTYPE_UC, 0);

	m = get_mqd(mqd);
	m->cp_hqd_vmid = q->vmid;
}