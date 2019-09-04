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
struct vpdma_desc_list {int /*<<< orphan*/ * next; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  vpdma_free_desc_buf (int /*<<< orphan*/ *) ; 

void vpdma_free_desc_list(struct vpdma_desc_list *list)
{
	vpdma_free_desc_buf(&list->buf);

	list->next = NULL;
}