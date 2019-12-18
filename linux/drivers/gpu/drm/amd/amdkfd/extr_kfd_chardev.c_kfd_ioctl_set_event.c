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
struct kfd_process {int dummy; } ;
struct kfd_ioctl_set_event_args {int /*<<< orphan*/  event_id; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int kfd_set_event (struct kfd_process*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kfd_ioctl_set_event(struct file *filp, struct kfd_process *p,
				void *data)
{
	struct kfd_ioctl_set_event_args *args = data;

	return kfd_set_event(p, args->event_id);
}