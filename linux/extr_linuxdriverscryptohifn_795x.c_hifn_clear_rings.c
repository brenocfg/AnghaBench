#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct hifn_dma {int cmdu; int srcu; int dstu; int resu; int cmdk; int srck; int dstk; int resk; int /*<<< orphan*/  resi; int /*<<< orphan*/  dsti; int /*<<< orphan*/  srci; int /*<<< orphan*/  cmdi; TYPE_4__* dstr; TYPE_3__* cmdr; TYPE_2__* srcr; TYPE_1__* resr; } ;
struct hifn_device {TYPE_5__* pdev; scalar_t__* sa; scalar_t__ reset; int /*<<< orphan*/  success; scalar_t__ desc_virt; } ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {int l; } ;
struct TYPE_8__ {int l; } ;
struct TYPE_7__ {int l; } ;
struct TYPE_6__ {int l; } ;

/* Variables and functions */
 int HIFN_D_CMD_RSIZE ; 
 int HIFN_D_DST_RSIZE ; 
 int HIFN_D_RES_RSIZE ; 
 int HIFN_D_SRC_RSIZE ; 
 int /*<<< orphan*/  HIFN_D_VALID ; 
 int __cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  hifn_complete_sa (struct hifn_device*,int) ; 
 int /*<<< orphan*/  hifn_process_ready (scalar_t__,int) ; 

__attribute__((used)) static void hifn_clear_rings(struct hifn_device *dev, int error)
{
	struct hifn_dma *dma = (struct hifn_dma *)dev->desc_virt;
	int i, u;

	dev_dbg(&dev->pdev->dev, "ring cleanup 1: i: %d.%d.%d.%d, u: %d.%d.%d.%d, "
			"k: %d.%d.%d.%d.\n",
			dma->cmdi, dma->srci, dma->dsti, dma->resi,
			dma->cmdu, dma->srcu, dma->dstu, dma->resu,
			dma->cmdk, dma->srck, dma->dstk, dma->resk);

	i = dma->resk; u = dma->resu;
	while (u != 0) {
		if (dma->resr[i].l & __cpu_to_le32(HIFN_D_VALID))
			break;

		if (dev->sa[i]) {
			dev->success++;
			dev->reset = 0;
			hifn_process_ready(dev->sa[i], error);
			hifn_complete_sa(dev, i);
		}

		if (++i == HIFN_D_RES_RSIZE)
			i = 0;
		u--;
	}
	dma->resk = i; dma->resu = u;

	i = dma->srck; u = dma->srcu;
	while (u != 0) {
		if (dma->srcr[i].l & __cpu_to_le32(HIFN_D_VALID))
			break;
		if (++i == HIFN_D_SRC_RSIZE)
			i = 0;
		u--;
	}
	dma->srck = i; dma->srcu = u;

	i = dma->cmdk; u = dma->cmdu;
	while (u != 0) {
		if (dma->cmdr[i].l & __cpu_to_le32(HIFN_D_VALID))
			break;
		if (++i == HIFN_D_CMD_RSIZE)
			i = 0;
		u--;
	}
	dma->cmdk = i; dma->cmdu = u;

	i = dma->dstk; u = dma->dstu;
	while (u != 0) {
		if (dma->dstr[i].l & __cpu_to_le32(HIFN_D_VALID))
			break;
		if (++i == HIFN_D_DST_RSIZE)
			i = 0;
		u--;
	}
	dma->dstk = i; dma->dstu = u;

	dev_dbg(&dev->pdev->dev, "ring cleanup 2: i: %d.%d.%d.%d, u: %d.%d.%d.%d, "
			"k: %d.%d.%d.%d.\n",
			dma->cmdi, dma->srci, dma->dsti, dma->resi,
			dma->cmdu, dma->srcu, dma->dstu, dma->resu,
			dma->cmdk, dma->srck, dma->dstk, dma->resk);
}