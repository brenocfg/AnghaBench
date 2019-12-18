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
struct priv {size_t cardno; } ;
struct net_device {int /*<<< orphan*/  base_addr; int /*<<< orphan*/  dma; struct priv* ml_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  total_size; } ;

/* Variables and functions */
 TYPE_1__* cards ; 
 int /*<<< orphan*/  disable_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ni65_free_buffer (struct priv*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cleanup_card(struct net_device *dev)
{
	struct priv *p = dev->ml_priv;
	disable_dma(dev->dma);
	free_dma(dev->dma);
	release_region(dev->base_addr, cards[p->cardno].total_size);
	ni65_free_buffer(p);
}