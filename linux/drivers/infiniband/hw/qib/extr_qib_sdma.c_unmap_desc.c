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
typedef  int u64 ;
struct qib_pportdata {TYPE_3__* dd; TYPE_1__* sdma_descq; } ;
typedef  int dma_addr_t ;
typedef  int /*<<< orphan*/  __le64 ;
struct TYPE_6__ {TYPE_2__* pcidev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/ * qw; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int,size_t,int /*<<< orphan*/ ) ; 
 int le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unmap_desc(struct qib_pportdata *ppd, unsigned head)
{
	__le64 *descqp = &ppd->sdma_descq[head].qw[0];
	u64 desc[2];
	dma_addr_t addr;
	size_t len;

	desc[0] = le64_to_cpu(descqp[0]);
	desc[1] = le64_to_cpu(descqp[1]);

	addr = (desc[1] << 32) | (desc[0] >> 32);
	len = (desc[0] >> 14) & (0x7ffULL << 2);
	dma_unmap_single(&ppd->dd->pcidev->dev, addr, len, DMA_TO_DEVICE);
}