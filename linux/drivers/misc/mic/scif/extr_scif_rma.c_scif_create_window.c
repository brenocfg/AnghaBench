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
typedef  scalar_t__ u64 ;
struct scif_window {int temp; struct scif_window* dma_addr; int /*<<< orphan*/  type; int /*<<< orphan*/  list; int /*<<< orphan*/  unregwq; void* unreg_state; int /*<<< orphan*/  regwq; void* reg_state; int /*<<< orphan*/  magic; scalar_t__ ep; int /*<<< orphan*/  offset; void* num_pages; } ;
struct scif_endpt {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* OP_IDLE ; 
 int /*<<< orphan*/  SCIFEP_MAGIC ; 
 int /*<<< orphan*/  SCIF_WINDOW_SELF ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  scif_free (struct scif_window*,int) ; 
 void* scif_zalloc (int) ; 

struct scif_window *scif_create_window(struct scif_endpt *ep, int nr_pages,
				       s64 offset, bool temp)
{
	struct scif_window *window;

	might_sleep();
	window = scif_zalloc(sizeof(*window));
	if (!window)
		goto error;

	window->dma_addr = scif_zalloc(nr_pages * sizeof(*window->dma_addr));
	if (!window->dma_addr)
		goto error_free_window;

	window->num_pages = scif_zalloc(nr_pages * sizeof(*window->num_pages));
	if (!window->num_pages)
		goto error_free_window;

	window->offset = offset;
	window->ep = (u64)ep;
	window->magic = SCIFEP_MAGIC;
	window->reg_state = OP_IDLE;
	init_waitqueue_head(&window->regwq);
	window->unreg_state = OP_IDLE;
	init_waitqueue_head(&window->unregwq);
	INIT_LIST_HEAD(&window->list);
	window->type = SCIF_WINDOW_SELF;
	window->temp = temp;
	return window;

error_free_window:
	scif_free(window->dma_addr,
		  nr_pages * sizeof(*window->dma_addr));
	scif_free(window, sizeof(*window));
error:
	return NULL;
}