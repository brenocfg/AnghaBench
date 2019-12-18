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
struct vpdma_buf {size_t size; int mapped; scalar_t__ addr; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long VPDMA_DESC_ALIGN ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ kzalloc (size_t,int /*<<< orphan*/ ) ; 

int vpdma_alloc_desc_buf(struct vpdma_buf *buf, size_t size)
{
	buf->size = size;
	buf->mapped = false;
	buf->addr = kzalloc(size, GFP_KERNEL);
	if (!buf->addr)
		return -ENOMEM;

	WARN_ON(((unsigned long)buf->addr & VPDMA_DESC_ALIGN) != 0);

	return 0;
}