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
struct jz4780_dma_desc {int /*<<< orphan*/  vdesc; TYPE_2__* desc; } ;
struct jz4780_dma_chan {int /*<<< orphan*/  vchan; TYPE_1__* desc; } ;
struct dma_chan {int dummy; } ;
struct dma_async_tx_descriptor {int dummy; } ;
typedef  enum dma_transfer_direction { ____Placeholder_dma_transfer_direction } dma_transfer_direction ;
typedef  size_t dma_addr_t ;
struct TYPE_4__ {int dcm; unsigned int dtc; } ;
struct TYPE_3__ {int /*<<< orphan*/  vdesc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_CYCLIC ; 
 int JZ_DMA_DCM_LINK ; 
 int JZ_DMA_DCM_TIE ; 
 struct jz4780_dma_desc* jz4780_dma_desc_alloc (struct jz4780_dma_chan*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jz4780_dma_desc_free (int /*<<< orphan*/ *) ; 
 int jz4780_dma_setup_hwdesc (struct jz4780_dma_chan*,TYPE_2__*,size_t,size_t,int) ; 
 struct jz4780_dma_chan* to_jz4780_dma_chan (struct dma_chan*) ; 
 struct dma_async_tx_descriptor* vchan_tx_prep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dma_async_tx_descriptor *jz4780_dma_prep_dma_cyclic(
	struct dma_chan *chan, dma_addr_t buf_addr, size_t buf_len,
	size_t period_len, enum dma_transfer_direction direction,
	unsigned long flags)
{
	struct jz4780_dma_chan *jzchan = to_jz4780_dma_chan(chan);
	struct jz4780_dma_desc *desc;
	unsigned int periods, i;
	int err;

	if (buf_len % period_len)
		return NULL;

	periods = buf_len / period_len;

	desc = jz4780_dma_desc_alloc(jzchan, periods, DMA_CYCLIC);
	if (!desc)
		return NULL;

	for (i = 0; i < periods; i++) {
		err = jz4780_dma_setup_hwdesc(jzchan, &desc->desc[i], buf_addr,
					      period_len, direction);
		if (err < 0) {
			jz4780_dma_desc_free(&jzchan->desc->vdesc);
			return NULL;
		}

		buf_addr += period_len;

		/*
		 * Set the link bit to indicate that the controller should
		 * automatically proceed to the next descriptor. In
		 * jz4780_dma_begin(), this will be cleared if we need to issue
		 * an interrupt after each period.
		 */
		desc->desc[i].dcm |= JZ_DMA_DCM_TIE | JZ_DMA_DCM_LINK;

		/*
		 * The upper 8 bits of the DTC field in the descriptor must be
		 * set to (offset from descriptor base of next descriptor >> 4).
		 * If this is the last descriptor, link it back to the first,
		 * i.e. leave offset set to 0, otherwise point to the next one.
		 */
		if (i != (periods - 1)) {
			desc->desc[i].dtc |=
				(((i + 1) * sizeof(*desc->desc)) >> 4) << 24;
		}
	}

	return vchan_tx_prep(&jzchan->vchan, &desc->vdesc, flags);
}