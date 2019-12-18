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
struct vb2_buffer {int /*<<< orphan*/  planes; int /*<<< orphan*/  vb2_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  buf_prepare ; 
 int call_bufop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int call_vb_qop (struct vb2_buffer*,int /*<<< orphan*/ ,struct vb2_buffer*) ; 
 int /*<<< orphan*/  fill_vb2_buffer ; 

__attribute__((used)) static int __prepare_mmap(struct vb2_buffer *vb)
{
	int ret = 0;

	ret = call_bufop(vb->vb2_queue, fill_vb2_buffer,
			 vb, vb->planes);
	return ret ? ret : call_vb_qop(vb, buf_prepare, vb);
}