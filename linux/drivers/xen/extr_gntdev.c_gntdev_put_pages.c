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
struct gntdev_copy_batch {unsigned int nr_pages; int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gntdev_put_pages(struct gntdev_copy_batch *batch)
{
	unsigned int i;

	for (i = 0; i < batch->nr_pages; i++)
		put_page(batch->pages[i]);
	batch->nr_pages = 0;
}