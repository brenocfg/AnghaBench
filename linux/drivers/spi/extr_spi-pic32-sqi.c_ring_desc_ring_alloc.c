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
struct ring_desc {int bd_dma; int /*<<< orphan*/  list; struct buf_desc* bd; } ;
struct pic32_sqi {int bd_dma; struct ring_desc* ring; int /*<<< orphan*/  bd_list_free; int /*<<< orphan*/  bd_list_used; scalar_t__ bd; TYPE_1__* master; } ;
struct buf_desc {int bd_nextp; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PESQI_BD_COUNT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int) ; 
 struct ring_desc* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ring_desc_ring_alloc(struct pic32_sqi *sqi)
{
	struct ring_desc *rdesc;
	struct buf_desc *bd;
	int i;

	/* allocate coherent DMAable memory for hardware buffer descriptors. */
	sqi->bd = dma_alloc_coherent(&sqi->master->dev,
				     sizeof(*bd) * PESQI_BD_COUNT,
				     &sqi->bd_dma, GFP_KERNEL);
	if (!sqi->bd) {
		dev_err(&sqi->master->dev, "failed allocating dma buffer\n");
		return -ENOMEM;
	}

	/* allocate software ring descriptors */
	sqi->ring = kcalloc(PESQI_BD_COUNT, sizeof(*rdesc), GFP_KERNEL);
	if (!sqi->ring) {
		dma_free_coherent(&sqi->master->dev,
				  sizeof(*bd) * PESQI_BD_COUNT,
				  sqi->bd, sqi->bd_dma);
		return -ENOMEM;
	}

	bd = (struct buf_desc *)sqi->bd;

	INIT_LIST_HEAD(&sqi->bd_list_free);
	INIT_LIST_HEAD(&sqi->bd_list_used);

	/* initialize ring-desc */
	for (i = 0, rdesc = sqi->ring; i < PESQI_BD_COUNT; i++, rdesc++) {
		INIT_LIST_HEAD(&rdesc->list);
		rdesc->bd = &bd[i];
		rdesc->bd_dma = sqi->bd_dma + (void *)&bd[i] - (void *)bd;
		list_add_tail(&rdesc->list, &sqi->bd_list_free);
	}

	/* Prepare BD: chain to next BD(s) */
	for (i = 0, rdesc = sqi->ring; i < PESQI_BD_COUNT - 1; i++)
		bd[i].bd_nextp = rdesc[i + 1].bd_dma;
	bd[PESQI_BD_COUNT - 1].bd_nextp = 0;

	return 0;
}