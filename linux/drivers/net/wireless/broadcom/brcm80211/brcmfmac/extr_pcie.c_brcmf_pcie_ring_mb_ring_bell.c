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
struct brcmf_pciedev_info {scalar_t__ state; } ;
struct brcmf_pcie_ringbuf {struct brcmf_pciedev_info* devinfo; } ;

/* Variables and functions */
 scalar_t__ BRCMFMAC_PCIE_STATE_UP ; 
 int /*<<< orphan*/  BRCMF_PCIE_PCIE2REG_H2D_MAILBOX_0 ; 
 int EIO ; 
 int /*<<< orphan*/  PCIE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_pcie_write_reg32 (struct brcmf_pciedev_info*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int brcmf_pcie_ring_mb_ring_bell(void *ctx)
{
	struct brcmf_pcie_ringbuf *ring = (struct brcmf_pcie_ringbuf *)ctx;
	struct brcmf_pciedev_info *devinfo = ring->devinfo;

	if (devinfo->state != BRCMFMAC_PCIE_STATE_UP)
		return -EIO;

	brcmf_dbg(PCIE, "RING !\n");
	/* Any arbitrary value will do, lets use 1 */
	brcmf_pcie_write_reg32(devinfo, BRCMF_PCIE_PCIE2REG_H2D_MAILBOX_0, 1);

	return 0;
}