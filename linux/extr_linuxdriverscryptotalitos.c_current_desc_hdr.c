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
typedef  int /*<<< orphan*/  u32 ;
struct talitos_private {int fifo_len; TYPE_3__* chan; } ;
struct device {int dummy; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {int tail; TYPE_2__* fifo; scalar_t__ reg; } ;
struct TYPE_5__ {int dma_desc; TYPE_1__* desc; } ;
struct TYPE_4__ {int next_desc; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 scalar_t__ TALITOS_CDPR ; 
 scalar_t__ TALITOS_CDPR_LO ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct talitos_private* dev_get_drvdata (struct device*) ; 
 int in_be32 (scalar_t__) ; 

__attribute__((used)) static u32 current_desc_hdr(struct device *dev, int ch)
{
	struct talitos_private *priv = dev_get_drvdata(dev);
	int tail, iter;
	dma_addr_t cur_desc;

	cur_desc = ((u64)in_be32(priv->chan[ch].reg + TALITOS_CDPR)) << 32;
	cur_desc |= in_be32(priv->chan[ch].reg + TALITOS_CDPR_LO);

	if (!cur_desc) {
		dev_err(dev, "CDPR is NULL, giving up search for offending descriptor\n");
		return 0;
	}

	tail = priv->chan[ch].tail;

	iter = tail;
	while (priv->chan[ch].fifo[iter].dma_desc != cur_desc &&
	       priv->chan[ch].fifo[iter].desc->next_desc != cur_desc) {
		iter = (iter + 1) & (priv->fifo_len - 1);
		if (iter == tail) {
			dev_err(dev, "couldn't locate current descriptor\n");
			return 0;
		}
	}

	if (priv->chan[ch].fifo[iter].desc->next_desc == cur_desc)
		return (priv->chan[ch].fifo[iter].desc + 1)->hdr;

	return priv->chan[ch].fifo[iter].desc->hdr;
}