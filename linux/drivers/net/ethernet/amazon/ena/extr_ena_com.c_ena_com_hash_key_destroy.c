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
struct ena_rss {int /*<<< orphan*/ * hash_key; int /*<<< orphan*/  hash_key_dma_addr; } ;
struct ena_com_dev {int /*<<< orphan*/  dmadev; struct ena_rss rss; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ena_com_hash_key_destroy(struct ena_com_dev *ena_dev)
{
	struct ena_rss *rss = &ena_dev->rss;

	if (rss->hash_key)
		dma_free_coherent(ena_dev->dmadev, sizeof(*rss->hash_key),
				  rss->hash_key, rss->hash_key_dma_addr);
	rss->hash_key = NULL;
}