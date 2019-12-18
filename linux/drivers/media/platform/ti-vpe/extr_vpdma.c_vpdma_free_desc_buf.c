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
struct vpdma_buf {scalar_t__ size; int /*<<< orphan*/ * addr; int /*<<< orphan*/  mapped; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void vpdma_free_desc_buf(struct vpdma_buf *buf)
{
	WARN_ON(buf->mapped);
	kfree(buf->addr);
	buf->addr = NULL;
	buf->size = 0;
}