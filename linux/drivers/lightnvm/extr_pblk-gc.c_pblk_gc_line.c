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
struct pblk_line_ws {int /*<<< orphan*/  ws; struct pblk_line* line; struct pblk* pblk; } ;
struct pblk_line {int /*<<< orphan*/  id; } ;
struct pblk_gc {int /*<<< orphan*/  gc_reader_wq; int /*<<< orphan*/  pipeline_gc; } ;
struct pblk {struct pblk_gc gc; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct pblk_line_ws* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_debug (struct pblk*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pblk_gc_line_prepare_ws ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pblk_gc_line(struct pblk *pblk, struct pblk_line *line)
{
	struct pblk_gc *gc = &pblk->gc;
	struct pblk_line_ws *line_ws;

	pblk_debug(pblk, "line '%d' being reclaimed for GC\n", line->id);

	line_ws = kmalloc(sizeof(struct pblk_line_ws), GFP_KERNEL);
	if (!line_ws)
		return -ENOMEM;

	line_ws->pblk = pblk;
	line_ws->line = line;

	atomic_inc(&gc->pipeline_gc);
	INIT_WORK(&line_ws->ws, pblk_gc_line_prepare_ws);
	queue_work(gc->gc_reader_wq, &line_ws->ws);

	return 0;
}