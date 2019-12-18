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
struct scif_window {int nr_pages; scalar_t__ magic; struct scif_window* num_pages; struct scif_window* dma_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  scif_free (struct scif_window*,int) ; 

void
scif_destroy_remote_window(struct scif_window *window)
{
	scif_free(window->dma_addr, window->nr_pages *
		  sizeof(*window->dma_addr));
	scif_free(window->num_pages, window->nr_pages *
		  sizeof(*window->num_pages));
	window->magic = 0;
	scif_free(window, sizeof(*window));
}