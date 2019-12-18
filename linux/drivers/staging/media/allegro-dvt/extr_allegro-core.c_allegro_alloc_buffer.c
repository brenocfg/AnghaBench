#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct allegro_dev {TYPE_1__* plat_dev; } ;
struct allegro_buffer {size_t size; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  paddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int allegro_alloc_buffer(struct allegro_dev *dev,
				struct allegro_buffer *buffer, size_t size)
{
	buffer->vaddr = dma_alloc_coherent(&dev->plat_dev->dev, size,
					   &buffer->paddr, GFP_KERNEL);
	if (!buffer->vaddr)
		return -ENOMEM;
	buffer->size = size;

	return 0;
}