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
struct uvc_fh {scalar_t__ state; TYPE_1__* stream; } ;
struct TYPE_2__ {int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ UVC_HANDLE_ACTIVE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int uvc_acquire_privileges(struct uvc_fh *handle)
{
	/* Always succeed if the handle is already privileged. */
	if (handle->state == UVC_HANDLE_ACTIVE)
		return 0;

	/* Check if the device already has a privileged handle. */
	if (atomic_inc_return(&handle->stream->active) != 1) {
		atomic_dec(&handle->stream->active);
		return -EBUSY;
	}

	handle->state = UVC_HANDLE_ACTIVE;
	return 0;
}