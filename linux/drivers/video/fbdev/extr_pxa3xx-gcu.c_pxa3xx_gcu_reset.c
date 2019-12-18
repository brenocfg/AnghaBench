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
struct pxa3xx_gcu_priv {int shared_phys; int /*<<< orphan*/  base_time; TYPE_1__* shared; } ;
struct TYPE_2__ {int buffer_phys; int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int GCCR_ABORT ; 
 int IE_ALL ; 
 int IE_EOB ; 
 int /*<<< orphan*/  PXA3XX_GCU_SHARED_MAGIC ; 
 int /*<<< orphan*/  QDUMP (char*) ; 
 int /*<<< orphan*/  REG_GCCR ; 
 int /*<<< orphan*/  REG_GCIECR ; 
 int /*<<< orphan*/  REG_GCRBBR ; 
 int /*<<< orphan*/  REG_GCRBLR ; 
 int /*<<< orphan*/  REG_GCRBTR ; 
 int /*<<< orphan*/  SHARED_SIZE ; 
 int /*<<< orphan*/  gc_writel (struct pxa3xx_gcu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ktime_get_ts64 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pxa3xx_gcu_reset(struct pxa3xx_gcu_priv *priv)
{
	QDUMP("RESET");

	/* disable interrupts */
	gc_writel(priv, REG_GCIECR, 0);

	/* reset hardware */
	gc_writel(priv, REG_GCCR, GCCR_ABORT);
	gc_writel(priv, REG_GCCR, 0);

	memset(priv->shared, 0, SHARED_SIZE);
	priv->shared->buffer_phys = priv->shared_phys;
	priv->shared->magic = PXA3XX_GCU_SHARED_MAGIC;

	ktime_get_ts64(&priv->base_time);

	/* set up the ring buffer pointers */
	gc_writel(priv, REG_GCRBLR, 0);
	gc_writel(priv, REG_GCRBBR, priv->shared_phys);
	gc_writel(priv, REG_GCRBTR, priv->shared_phys);

	/* enable all IRQs except EOB */
	gc_writel(priv, REG_GCIECR, IE_ALL & ~IE_EOB);
}