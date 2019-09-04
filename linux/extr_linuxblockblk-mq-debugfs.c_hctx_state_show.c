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
struct seq_file {int dummy; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_flags_show (struct seq_file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hctx_state_name ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int hctx_state_show(void *data, struct seq_file *m)
{
	struct blk_mq_hw_ctx *hctx = data;

	blk_flags_show(m, hctx->state, hctx_state_name,
		       ARRAY_SIZE(hctx_state_name));
	seq_puts(m, "\n");
	return 0;
}