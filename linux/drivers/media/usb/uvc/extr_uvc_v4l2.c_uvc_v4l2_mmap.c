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
struct vm_area_struct {int dummy; } ;
struct uvc_streaming {int /*<<< orphan*/  queue; } ;
struct uvc_fh {struct uvc_streaming* stream; } ;
struct file {struct uvc_fh* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  UVC_TRACE_CALLS ; 
 int uvc_queue_mmap (int /*<<< orphan*/ *,struct vm_area_struct*) ; 
 int /*<<< orphan*/  uvc_trace (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int uvc_v4l2_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct uvc_fh *handle = file->private_data;
	struct uvc_streaming *stream = handle->stream;

	uvc_trace(UVC_TRACE_CALLS, "uvc_v4l2_mmap\n");

	return uvc_queue_mmap(&stream->queue, vma);
}