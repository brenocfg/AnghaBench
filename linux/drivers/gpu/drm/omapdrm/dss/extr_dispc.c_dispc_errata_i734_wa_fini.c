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
struct dispc_device {TYPE_2__* pdev; TYPE_1__* feat; } ;
struct TYPE_6__ {int /*<<< orphan*/  paddr; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  has_gamma_i734_bug; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ i734_buf ; 

__attribute__((used)) static void dispc_errata_i734_wa_fini(struct dispc_device *dispc)
{
	if (!dispc->feat->has_gamma_i734_bug)
		return;

	dma_free_wc(&dispc->pdev->dev, i734_buf.size, i734_buf.vaddr,
		    i734_buf.paddr);
}