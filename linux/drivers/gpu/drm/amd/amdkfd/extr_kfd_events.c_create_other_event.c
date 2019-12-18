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
typedef  scalar_t__ uint32_t ;
struct kfd_process {int /*<<< orphan*/  event_idr; } ;
struct kfd_event {int event_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KFD_FIRST_NONSIGNAL_EVENT_ID ; 
 scalar_t__ KFD_LAST_NONSIGNAL_EVENT_ID ; 
 int idr_alloc (int /*<<< orphan*/ *,struct kfd_event*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_other_event(struct kfd_process *p, struct kfd_event *ev)
{
	/* Cast KFD_LAST_NONSIGNAL_EVENT to uint32_t. This allows an
	 * intentional integer overflow to -1 without a compiler
	 * warning. idr_alloc treats a negative value as "maximum
	 * signed integer".
	 */
	int id = idr_alloc(&p->event_idr, ev, KFD_FIRST_NONSIGNAL_EVENT_ID,
			   (uint32_t)KFD_LAST_NONSIGNAL_EVENT_ID + 1,
			   GFP_KERNEL);

	if (id < 0)
		return id;
	ev->event_id = id;

	return 0;
}