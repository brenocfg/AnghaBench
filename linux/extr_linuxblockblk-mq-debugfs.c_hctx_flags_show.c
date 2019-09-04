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
struct blk_mq_hw_ctx {int flags; } ;

/* Variables and functions */
 int const ARRAY_SIZE (char**) ; 
 int BLK_ALLOC_POLICY_TO_MQ_FLAG (int const) ; 
 int BLK_MQ_FLAG_TO_ALLOC_POLICY (int) ; 
 char** alloc_policy_name ; 
 int /*<<< orphan*/  blk_flags_show (struct seq_file*,int,char**,int const) ; 
 char** hctx_flag_name ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int const) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int hctx_flags_show(void *data, struct seq_file *m)
{
	struct blk_mq_hw_ctx *hctx = data;
	const int alloc_policy = BLK_MQ_FLAG_TO_ALLOC_POLICY(hctx->flags);

	seq_puts(m, "alloc_policy=");
	if (alloc_policy < ARRAY_SIZE(alloc_policy_name) &&
	    alloc_policy_name[alloc_policy])
		seq_puts(m, alloc_policy_name[alloc_policy]);
	else
		seq_printf(m, "%d", alloc_policy);
	seq_puts(m, " ");
	blk_flags_show(m,
		       hctx->flags ^ BLK_ALLOC_POLICY_TO_MQ_FLAG(alloc_policy),
		       hctx_flag_name, ARRAY_SIZE(hctx_flag_name));
	seq_puts(m, "\n");
	return 0;
}