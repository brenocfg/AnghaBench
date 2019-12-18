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
struct sh_veu_file {TYPE_1__* veu_dev; } ;
struct poll_table_struct {int dummy; } ;
struct file {struct sh_veu_file* private_data; } ;
typedef  int /*<<< orphan*/  __poll_t ;
struct TYPE_2__ {int /*<<< orphan*/  m2m_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  v4l2_m2m_poll (struct file*,int /*<<< orphan*/ ,struct poll_table_struct*) ; 

__attribute__((used)) static __poll_t sh_veu_poll(struct file *file,
				struct poll_table_struct *wait)
{
	struct sh_veu_file *veu_file = file->private_data;

	return v4l2_m2m_poll(file, veu_file->veu_dev->m2m_ctx, wait);
}