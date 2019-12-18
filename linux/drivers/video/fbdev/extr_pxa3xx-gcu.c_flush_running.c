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
struct pxa3xx_gcu_priv {struct pxa3xx_gcu_batch* running; struct pxa3xx_gcu_batch* free; } ;
struct pxa3xx_gcu_batch {struct pxa3xx_gcu_batch* next; } ;

/* Variables and functions */

__attribute__((used)) static void
flush_running(struct pxa3xx_gcu_priv *priv)
{
	struct pxa3xx_gcu_batch *running = priv->running;
	struct pxa3xx_gcu_batch *next;

	while (running) {
		next = running->next;
		running->next = priv->free;
		priv->free = running;
		running = next;
	}

	priv->running = NULL;
}