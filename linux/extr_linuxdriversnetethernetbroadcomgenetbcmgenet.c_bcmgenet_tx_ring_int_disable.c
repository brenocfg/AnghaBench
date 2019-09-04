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
struct bcmgenet_tx_ring {int index; int /*<<< orphan*/  priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  INTRL2_CPU_MASK_SET ; 
 int /*<<< orphan*/  bcmgenet_intrl2_1_writel (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcmgenet_tx_ring_int_disable(struct bcmgenet_tx_ring *ring)
{
	bcmgenet_intrl2_1_writel(ring->priv, 1 << ring->index,
				 INTRL2_CPU_MASK_SET);
}