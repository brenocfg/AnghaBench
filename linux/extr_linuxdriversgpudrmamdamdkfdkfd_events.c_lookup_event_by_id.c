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
typedef  int /*<<< orphan*/  uint32_t ;
struct kfd_process {int /*<<< orphan*/  event_idr; } ;
struct kfd_event {int dummy; } ;

/* Variables and functions */
 struct kfd_event* idr_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kfd_event *lookup_event_by_id(struct kfd_process *p, uint32_t id)
{
	return idr_find(&p->event_idr, id);
}