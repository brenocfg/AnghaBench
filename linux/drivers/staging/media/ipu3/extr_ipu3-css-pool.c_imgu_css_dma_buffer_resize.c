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
struct imgu_device {TYPE_1__* pci_dev; } ;
struct imgu_css_map {size_t size; scalar_t__ vaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,size_t,size_t) ; 
 int /*<<< orphan*/  imgu_dmamap_alloc (struct imgu_device*,struct imgu_css_map*,size_t) ; 
 int /*<<< orphan*/  imgu_dmamap_free (struct imgu_device*,struct imgu_css_map*) ; 

int imgu_css_dma_buffer_resize(struct imgu_device *imgu,
			       struct imgu_css_map *map, size_t size)
{
	if (map->size < size && map->vaddr) {
		dev_warn(&imgu->pci_dev->dev, "dma buf resized from %zu to %zu",
			 map->size, size);

		imgu_dmamap_free(imgu, map);
		if (!imgu_dmamap_alloc(imgu, map, size))
			return -ENOMEM;
	}

	return 0;
}