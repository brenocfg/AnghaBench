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
struct pic32_sqi {int /*<<< orphan*/  ring; int /*<<< orphan*/  bd_dma; int /*<<< orphan*/  bd; TYPE_1__* master; } ;
struct buf_desc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int PESQI_BD_COUNT ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ring_desc_ring_free(struct pic32_sqi *sqi)
{
	dma_free_coherent(&sqi->master->dev,
			  sizeof(struct buf_desc) * PESQI_BD_COUNT,
			  sqi->bd, sqi->bd_dma);
	kfree(sqi->ring);
}