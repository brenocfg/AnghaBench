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
typedef  scalar_t__ u32 ;
struct sti_hqvdp_cmd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  notifier_call; } ;
struct sti_hqvdp {int /*<<< orphan*/  hqvdp_cmd; scalar_t__ hqvdp_cmd_paddr; int /*<<< orphan*/  dev; TYPE_1__ vtg_nb; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int GFP_DMA ; 
 int GFP_KERNEL ; 
 int NB_VDP_CMD ; 
 int /*<<< orphan*/  dma_alloc_wc (int /*<<< orphan*/ ,int,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sti_hqvdp_vtg_cb ; 

__attribute__((used)) static void sti_hqvdp_init(struct sti_hqvdp *hqvdp)
{
	int size;
	dma_addr_t dma_addr;

	hqvdp->vtg_nb.notifier_call = sti_hqvdp_vtg_cb;

	/* Allocate memory for the VDP commands */
	size = NB_VDP_CMD * sizeof(struct sti_hqvdp_cmd);
	hqvdp->hqvdp_cmd = dma_alloc_wc(hqvdp->dev, size,
					&dma_addr,
					GFP_KERNEL | GFP_DMA);
	if (!hqvdp->hqvdp_cmd) {
		DRM_ERROR("Failed to allocate memory for VDP cmd\n");
		return;
	}

	hqvdp->hqvdp_cmd_paddr = (u32)dma_addr;
	memset(hqvdp->hqvdp_cmd, 0, size);
}