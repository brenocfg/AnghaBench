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
struct pxa3xx_gcu_shared {int* buffer; int hw_running; unsigned int buffer_phys; } ;
struct pxa3xx_gcu_priv {int /*<<< orphan*/ * ready_last; struct pxa3xx_gcu_batch* ready; struct pxa3xx_gcu_batch* running; struct pxa3xx_gcu_shared* shared; } ;
struct pxa3xx_gcu_batch {int phys; struct pxa3xx_gcu_batch* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  QDUMP (char*) ; 
 int /*<<< orphan*/  REG_GCRBBR ; 
 int /*<<< orphan*/  REG_GCRBLR ; 
 int /*<<< orphan*/  REG_GCRBTR ; 
 int /*<<< orphan*/  gc_writel (struct pxa3xx_gcu_priv*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
run_ready(struct pxa3xx_gcu_priv *priv)
{
	unsigned int num = 0;
	struct pxa3xx_gcu_shared *shared = priv->shared;
	struct pxa3xx_gcu_batch	*ready = priv->ready;

	QDUMP("Start");

	BUG_ON(!ready);

	shared->buffer[num++] = 0x05000000;

	while (ready) {
		shared->buffer[num++] = 0x00000001;
		shared->buffer[num++] = ready->phys;
		ready = ready->next;
	}

	shared->buffer[num++] = 0x05000000;
	priv->running = priv->ready;
	priv->ready = priv->ready_last = NULL;
	gc_writel(priv, REG_GCRBLR, 0);
	shared->hw_running = 1;

	/* ring base address */
	gc_writel(priv, REG_GCRBBR, shared->buffer_phys);

	/* ring tail address */
	gc_writel(priv, REG_GCRBTR, shared->buffer_phys + num * 4);

	/* ring length */
	gc_writel(priv, REG_GCRBLR, ((num + 63) & ~63) * 4);
}