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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  il4965_rx_allocate (struct il_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_rx_queue_restock (struct il_priv*) ; 

void
il4965_rx_replenish_now(struct il_priv *il)
{
	il4965_rx_allocate(il, GFP_ATOMIC);

	il4965_rx_queue_restock(il);
}