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
struct cmdq_pkt {int dummy; } ;
struct cmdq_flush_completion {int err; int /*<<< orphan*/  cmplt; } ;

/* Variables and functions */
 int EFAULT ; 
 int cmdq_pkt_flush_async (struct cmdq_pkt*,int /*<<< orphan*/ ,struct cmdq_flush_completion*) ; 
 int /*<<< orphan*/  cmdq_pkt_flush_cb ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int cmdq_pkt_flush(struct cmdq_pkt *pkt)
{
	struct cmdq_flush_completion cmplt;
	int err;

	init_completion(&cmplt.cmplt);
	err = cmdq_pkt_flush_async(pkt, cmdq_pkt_flush_cb, &cmplt);
	if (err < 0)
		return err;
	wait_for_completion(&cmplt.cmplt);

	return cmplt.err ? -EFAULT : 0;
}