#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pt3_board {TYPE_3__* pdev; } ;
struct TYPE_5__ {struct pt3_board* priv; } ;
struct pt3_adapter {int num_bufs; int num_desc_bufs; TYPE_4__* desc_buf; TYPE_2__* buffer; TYPE_1__ dvb_adap; } ;
struct TYPE_8__ {int /*<<< orphan*/  b_addr; int /*<<< orphan*/  descs; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  b_addr; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DATA_BUF_SZ ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void pt3_free_dmabuf(struct pt3_adapter *adap)
{
	struct pt3_board *pt3;
	int i;

	pt3 = adap->dvb_adap.priv;
	for (i = 0; i < adap->num_bufs; i++)
		dma_free_coherent(&pt3->pdev->dev, DATA_BUF_SZ,
			adap->buffer[i].data, adap->buffer[i].b_addr);
	adap->num_bufs = 0;

	for (i = 0; i < adap->num_desc_bufs; i++)
		dma_free_coherent(&pt3->pdev->dev, PAGE_SIZE,
			adap->desc_buf[i].descs, adap->desc_buf[i].b_addr);
	adap->num_desc_bufs = 0;
}