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
struct allegro_buffer {scalar_t__ size; int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  paddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void allegro_free_buffer(struct allegro_dev *dev,
				struct allegro_buffer *buffer)
{
	if (buffer->vaddr) {
		dma_free_coherent(&dev->plat_dev->dev, buffer->size,
				  buffer->vaddr, buffer->paddr);
		buffer->vaddr = NULL;
		buffer->size = 0;
	}
}