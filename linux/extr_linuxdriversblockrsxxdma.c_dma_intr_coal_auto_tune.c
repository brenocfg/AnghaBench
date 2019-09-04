#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ mode; int /*<<< orphan*/  latency; } ;
struct TYPE_9__ {TYPE_3__ intr_coal; } ;
struct TYPE_10__ {TYPE_4__ data; } ;
struct rsxx_cardinfo {int n_targets; scalar_t__ regmap; TYPE_5__ config; TYPE_2__* ctrl; int /*<<< orphan*/  eeh_state; } ;
struct TYPE_6__ {int /*<<< orphan*/  hw_q_depth; } ;
struct TYPE_7__ {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ INTR_COAL ; 
 scalar_t__ RSXX_INTR_COAL_AUTO_TUNE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int dma_intr_coal_val (scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int,scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dma_intr_coal_auto_tune(struct rsxx_cardinfo *card)
{
	int i;
	u32 q_depth = 0;
	u32 intr_coal;

	if (card->config.data.intr_coal.mode != RSXX_INTR_COAL_AUTO_TUNE ||
	    unlikely(card->eeh_state))
		return;

	for (i = 0; i < card->n_targets; i++)
		q_depth += atomic_read(&card->ctrl[i].stats.hw_q_depth);

	intr_coal = dma_intr_coal_val(card->config.data.intr_coal.mode,
				      q_depth / 2,
				      card->config.data.intr_coal.latency);
	iowrite32(intr_coal, card->regmap + INTR_COAL);
}