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
struct vm_area_struct {int dummy; } ;
struct sh_veu_file {TYPE_1__* veu_dev; } ;
struct file {struct sh_veu_file* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;

/* Variables and functions */
 int v4l2_m2m_mmap (struct file*,int /*<<< orphan*/ ,struct vm_area_struct*) ; 

__attribute__((used)) static int sh_veu_mmap(struct file *file, struct vm_area_struct *vma)
{
	struct sh_veu_file *veu_file = file->private_data;

	return v4l2_m2m_mmap(file, veu_file->veu_dev->m2m_ctx, vma);
}