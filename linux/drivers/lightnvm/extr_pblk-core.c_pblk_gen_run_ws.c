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
struct workqueue_struct {int dummy; } ;
struct pblk_line_ws {int /*<<< orphan*/  ws; void* priv; struct pblk_line* line; struct pblk* pblk; } ;
struct pblk_line {int dummy; } ;
struct pblk {int /*<<< orphan*/  gen_ws_pool; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,void (*) (struct work_struct*)) ; 
 struct pblk_line_ws* mempool_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_work (struct workqueue_struct*,int /*<<< orphan*/ *) ; 

void pblk_gen_run_ws(struct pblk *pblk, struct pblk_line *line, void *priv,
		      void (*work)(struct work_struct *), gfp_t gfp_mask,
		      struct workqueue_struct *wq)
{
	struct pblk_line_ws *line_ws;

	line_ws = mempool_alloc(&pblk->gen_ws_pool, gfp_mask);

	line_ws->pblk = pblk;
	line_ws->line = line;
	line_ws->priv = priv;

	INIT_WORK(&line_ws->ws, work);
	queue_work(wq, &line_ws->ws);
}