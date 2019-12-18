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
struct seq_file {struct prism2_download_aux_dump* private; } ;
struct prism2_download_aux_dump {TYPE_1__* local; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ prism2_download_aux_dump_npages ; 
 int /*<<< orphan*/  prism2_enable_aux_port (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void *prism2_download_aux_dump_proc_start(struct seq_file *m, loff_t *_pos)
{
	struct prism2_download_aux_dump *ctx = m->private;
	prism2_enable_aux_port(ctx->local->dev, 1);
	if (*_pos >= prism2_download_aux_dump_npages)
		return NULL;
	return (void *)((unsigned long)*_pos + 1);
}