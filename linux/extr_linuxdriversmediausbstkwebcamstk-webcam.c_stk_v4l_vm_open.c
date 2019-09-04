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
struct vm_area_struct {struct stk_sio_buffer* vm_private_data; } ;
struct stk_sio_buffer {int /*<<< orphan*/  mapcount; } ;

/* Variables and functions */

__attribute__((used)) static void stk_v4l_vm_open(struct vm_area_struct *vma)
{
	struct stk_sio_buffer *sbuf = vma->vm_private_data;
	sbuf->mapcount++;
}