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
struct xfer_desc {void* next_h; void* next_l; scalar_t__ size; void* addr_h; void* addr_l; } ;
struct pt3_board {int num_bufs; TYPE_2__* pdev; } ;
struct TYPE_5__ {struct pt3_board* priv; } ;
struct pt3_adapter {int num_bufs; TYPE_4__* desc_buf; TYPE_3__* buffer; int /*<<< orphan*/  num_desc_bufs; TYPE_1__ dvb_adap; } ;
typedef  scalar_t__ dma_addr_t ;
struct TYPE_8__ {scalar_t__ b_addr; struct xfer_desc* descs; } ;
struct TYPE_7__ {scalar_t__ b_addr; void* data; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DATA_BUF_SZ ; 
 int DATA_BUF_XFERS ; 
 scalar_t__ DATA_XFER_SZ ; 
 int DESCS_IN_PAGE ; 
 int DIV_ROUND_UP (int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PAGE_SIZE ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 void* lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  pt3_free_dmabuf (struct pt3_adapter*) ; 
 int /*<<< orphan*/  pt3_init_dmabuf (struct pt3_adapter*) ; 
 void* upper_32_bits (scalar_t__) ; 

int pt3_alloc_dmabuf(struct pt3_adapter *adap)
{
	struct pt3_board *pt3;
	void *p;
	int i, j;
	int idx, ofs;
	int num_desc_bufs;
	dma_addr_t data_addr, desc_addr;
	struct xfer_desc *d;

	pt3 = adap->dvb_adap.priv;
	adap->num_bufs = 0;
	adap->num_desc_bufs = 0;
	for (i = 0; i < pt3->num_bufs; i++) {
		p = dma_alloc_coherent(&pt3->pdev->dev, DATA_BUF_SZ,
					&adap->buffer[i].b_addr, GFP_KERNEL);
		if (p == NULL)
			goto failed;
		adap->buffer[i].data = p;
		adap->num_bufs++;
	}
	pt3_init_dmabuf(adap);

	/* build circular-linked pointers (xfer_desc) to the data buffers*/
	idx = 0;
	ofs = 0;
	num_desc_bufs =
		DIV_ROUND_UP(adap->num_bufs * DATA_BUF_XFERS, DESCS_IN_PAGE);
	for (i = 0; i < num_desc_bufs; i++) {
		p = dma_alloc_coherent(&pt3->pdev->dev, PAGE_SIZE,
					&desc_addr, GFP_KERNEL);
		if (p == NULL)
			goto failed;
		adap->num_desc_bufs++;
		adap->desc_buf[i].descs = p;
		adap->desc_buf[i].b_addr = desc_addr;

		if (i > 0) {
			d = &adap->desc_buf[i - 1].descs[DESCS_IN_PAGE - 1];
			d->next_l = lower_32_bits(desc_addr);
			d->next_h = upper_32_bits(desc_addr);
		}
		for (j = 0; j < DESCS_IN_PAGE; j++) {
			data_addr = adap->buffer[idx].b_addr + ofs;
			d = &adap->desc_buf[i].descs[j];
			d->addr_l = lower_32_bits(data_addr);
			d->addr_h = upper_32_bits(data_addr);
			d->size = DATA_XFER_SZ;

			desc_addr += sizeof(struct xfer_desc);
			d->next_l = lower_32_bits(desc_addr);
			d->next_h = upper_32_bits(desc_addr);

			ofs += DATA_XFER_SZ;
			if (ofs >= DATA_BUF_SZ) {
				ofs -= DATA_BUF_SZ;
				idx++;
				if (idx >= adap->num_bufs) {
					desc_addr = adap->desc_buf[0].b_addr;
					d->next_l = lower_32_bits(desc_addr);
					d->next_h = upper_32_bits(desc_addr);
					return 0;
				}
			}
		}
	}
	return 0;

failed:
	pt3_free_dmabuf(adap);
	return -ENOMEM;
}