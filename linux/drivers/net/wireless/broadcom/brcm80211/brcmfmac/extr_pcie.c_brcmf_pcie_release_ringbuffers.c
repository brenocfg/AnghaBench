#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct TYPE_3__ {int /*<<< orphan*/ * flowrings; int /*<<< orphan*/ ** commonrings; } ;
struct brcmf_pciedev_info {int /*<<< orphan*/ * idxbuf; int /*<<< orphan*/  idxbuf_dmahandle; int /*<<< orphan*/  idxbuf_sz; TYPE_2__* pdev; TYPE_1__ shared; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t BRCMF_NROF_COMMON_MSGRINGS ; 
 int /*<<< orphan*/  brcmf_pcie_release_ringbuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brcmf_pcie_release_ringbuffers(struct brcmf_pciedev_info *devinfo)
{
	u32 i;

	for (i = 0; i < BRCMF_NROF_COMMON_MSGRINGS; i++) {
		brcmf_pcie_release_ringbuffer(&devinfo->pdev->dev,
					      devinfo->shared.commonrings[i]);
		devinfo->shared.commonrings[i] = NULL;
	}
	kfree(devinfo->shared.flowrings);
	devinfo->shared.flowrings = NULL;
	if (devinfo->idxbuf) {
		dma_free_coherent(&devinfo->pdev->dev,
				  devinfo->idxbuf_sz,
				  devinfo->idxbuf,
				  devinfo->idxbuf_dmahandle);
		devinfo->idxbuf = NULL;
	}
}