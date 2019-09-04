#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sa11x0_dma_chan {int /*<<< orphan*/  name; } ;
struct dma_chan {TYPE_2__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * driver; } ;

/* Variables and functions */
 TYPE_3__ sa11x0_dma_driver ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 struct sa11x0_dma_chan* to_sa11x0_dma_chan (struct dma_chan*) ; 

bool sa11x0_dma_filter_fn(struct dma_chan *chan, void *param)
{
	if (chan->device->dev->driver == &sa11x0_dma_driver.driver) {
		struct sa11x0_dma_chan *c = to_sa11x0_dma_chan(chan);
		const char *p = param;

		return !strcmp(c->name, p);
	}
	return false;
}