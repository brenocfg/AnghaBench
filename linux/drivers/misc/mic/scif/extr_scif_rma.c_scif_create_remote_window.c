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
struct scif_window {int nr_pages; int /*<<< orphan*/  list; int /*<<< orphan*/  unreg_state; int /*<<< orphan*/  type; void* num_pages; void* dma_addr; int /*<<< orphan*/  magic; } ;
struct scif_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OP_IDLE ; 
 int /*<<< orphan*/  SCIFEP_MAGIC ; 
 int /*<<< orphan*/  SCIF_WINDOW_PEER ; 
 int /*<<< orphan*/  might_sleep () ; 
 scalar_t__ scif_create_remote_lookup (struct scif_dev*,struct scif_window*) ; 
 int /*<<< orphan*/  scif_destroy_remote_window (struct scif_window*) ; 
 void* scif_zalloc (int) ; 

__attribute__((used)) static struct scif_window *
scif_create_remote_window(struct scif_dev *scifdev, int nr_pages)
{
	struct scif_window *window;

	might_sleep();
	window = scif_zalloc(sizeof(*window));
	if (!window)
		goto error_ret;

	window->magic = SCIFEP_MAGIC;
	window->nr_pages = nr_pages;

	window->dma_addr = scif_zalloc(nr_pages * sizeof(*window->dma_addr));
	if (!window->dma_addr)
		goto error_window;

	window->num_pages = scif_zalloc(nr_pages *
					sizeof(*window->num_pages));
	if (!window->num_pages)
		goto error_window;

	if (scif_create_remote_lookup(scifdev, window))
		goto error_window;

	window->type = SCIF_WINDOW_PEER;
	window->unreg_state = OP_IDLE;
	INIT_LIST_HEAD(&window->list);
	return window;
error_window:
	scif_destroy_remote_window(window);
error_ret:
	return NULL;
}