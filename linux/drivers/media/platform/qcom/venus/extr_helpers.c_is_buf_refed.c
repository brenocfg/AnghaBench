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
struct venus_inst {int /*<<< orphan*/  delayed_process_work; int /*<<< orphan*/  delayed_process; } ;
struct venus_buffer {int flags; int /*<<< orphan*/  ref_list; } ;
struct vb2_v4l2_buffer {int dummy; } ;

/* Variables and functions */
 int HFI_BUFFERFLAG_READONLY ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 struct venus_buffer* to_venus_buffer (struct vb2_v4l2_buffer*) ; 

__attribute__((used)) static int is_buf_refed(struct venus_inst *inst, struct vb2_v4l2_buffer *vbuf)
{
	struct venus_buffer *buf = to_venus_buffer(vbuf);

	if (buf->flags & HFI_BUFFERFLAG_READONLY) {
		list_add_tail(&buf->ref_list, &inst->delayed_process);
		schedule_work(&inst->delayed_process_work);
		return 1;
	}

	return 0;
}