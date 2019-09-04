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
struct device {int dummy; } ;
struct artpec6_crypto_req_common {struct artpec6_crypto_dma_descriptors* dma; } ;
struct artpec6_crypto_dma_map {int /*<<< orphan*/  dir; int /*<<< orphan*/  size; int /*<<< orphan*/  dma_addr; } ;
struct artpec6_crypto_dma_descriptors {int map_count; struct artpec6_crypto_dma_map* maps; } ;

/* Variables and functions */
 struct device* artpec6_crypto_dev ; 
 int /*<<< orphan*/  dma_unmap_page (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
artpec6_crypto_dma_unmap_all(struct artpec6_crypto_req_common *common)
{
	struct artpec6_crypto_dma_descriptors *dma = common->dma;
	struct device *dev = artpec6_crypto_dev;
	int i;

	for (i = 0; i < dma->map_count; i++) {
		struct artpec6_crypto_dma_map *map = &dma->maps[i];

		dma_unmap_page(dev, map->dma_addr, map->size, map->dir);
	}

	dma->map_count = 0;
}