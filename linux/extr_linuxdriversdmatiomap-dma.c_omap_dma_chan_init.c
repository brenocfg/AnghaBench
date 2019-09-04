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
struct omap_dmadev {int /*<<< orphan*/  ddev; int /*<<< orphan*/  reg_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  desc_free; } ;
struct omap_chan {TYPE_1__ vc; int /*<<< orphan*/  reg_map; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct omap_chan* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_dma_desc_free ; 
 int /*<<< orphan*/  vchan_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int omap_dma_chan_init(struct omap_dmadev *od)
{
	struct omap_chan *c;

	c = kzalloc(sizeof(*c), GFP_KERNEL);
	if (!c)
		return -ENOMEM;

	c->reg_map = od->reg_map;
	c->vc.desc_free = omap_dma_desc_free;
	vchan_init(&c->vc, &od->ddev);

	return 0;
}