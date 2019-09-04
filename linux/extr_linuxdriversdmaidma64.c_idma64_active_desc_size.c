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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct idma64_hw_desc {scalar_t__ llp; scalar_t__ len; } ;
struct idma64_desc {size_t length; unsigned int ndesc; struct idma64_hw_desc* hw; } ;
struct idma64_chan {struct idma64_desc* desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_HI ; 
 size_t IDMA64C_CTLH_BLOCK_TS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LLP ; 
 int /*<<< orphan*/  channel_readl (struct idma64_chan*,int /*<<< orphan*/ ) ; 
 scalar_t__ channel_readq (struct idma64_chan*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t idma64_active_desc_size(struct idma64_chan *idma64c)
{
	struct idma64_desc *desc = idma64c->desc;
	struct idma64_hw_desc *hw;
	size_t bytes = desc->length;
	u64 llp = channel_readq(idma64c, LLP);
	u32 ctlhi = channel_readl(idma64c, CTL_HI);
	unsigned int i = 0;

	do {
		hw = &desc->hw[i];
		if (hw->llp == llp)
			break;
		bytes -= hw->len;
	} while (++i < desc->ndesc);

	if (!i)
		return bytes;

	/* The current chunk is not fully transfered yet */
	bytes += desc->hw[--i].len;

	return bytes - IDMA64C_CTLH_BLOCK_TS(ctlhi);
}