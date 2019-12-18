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
struct srp_iu {struct srp_iu* buf; int /*<<< orphan*/  direction; int /*<<< orphan*/  size; int /*<<< orphan*/  dma; } ;
struct srp_host {TYPE_1__* srp_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct srp_iu*) ; 

__attribute__((used)) static void srp_free_iu(struct srp_host *host, struct srp_iu *iu)
{
	if (!iu)
		return;

	ib_dma_unmap_single(host->srp_dev->dev, iu->dma, iu->size,
			    iu->direction);
	kfree(iu->buf);
	kfree(iu);
}