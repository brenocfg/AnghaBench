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
typedef  int /*<<< orphan*/  u16 ;
struct omap_desc {scalar_t__ sglen; int /*<<< orphan*/  vd; scalar_t__ using_ll; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct omap_chan {scalar_t__ sgidx; TYPE_1__ vc; scalar_t__ cyclic; struct omap_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  omap_dma_start_desc (struct omap_chan*) ; 
 int /*<<< orphan*/  omap_dma_start_sg (struct omap_chan*,struct omap_desc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void omap_dma_callback(int ch, u16 status, void *data)
{
	struct omap_chan *c = data;
	struct omap_desc *d;
	unsigned long flags;

	spin_lock_irqsave(&c->vc.lock, flags);
	d = c->desc;
	if (d) {
		if (c->cyclic) {
			vchan_cyclic_callback(&d->vd);
		} else if (d->using_ll || c->sgidx == d->sglen) {
			omap_dma_start_desc(c);
			vchan_cookie_complete(&d->vd);
		} else {
			omap_dma_start_sg(c, d);
		}
	}
	spin_unlock_irqrestore(&c->vc.lock, flags);
}