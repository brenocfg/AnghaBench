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
typedef  int /*<<< orphan*/  u64 ;
struct idma64_lli {int ctllo; } ;
struct idma64_hw_desc {scalar_t__ len; int /*<<< orphan*/  llp; struct idma64_lli* lli; } ;
struct idma64_desc {unsigned int ndesc; int /*<<< orphan*/  length; int /*<<< orphan*/  direction; struct idma64_hw_desc* hw; } ;
struct dma_slave_config {int dummy; } ;
struct idma64_chan {struct dma_slave_config config; } ;

/* Variables and functions */
 int IDMA64C_CTLL_INT_EN ; 
 int IDMA64C_CTLL_LLP_D_EN ; 
 int IDMA64C_CTLL_LLP_S_EN ; 
 int /*<<< orphan*/  idma64_hw_desc_fill (struct idma64_hw_desc*,struct dma_slave_config*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idma64_desc_fill(struct idma64_chan *idma64c,
		struct idma64_desc *desc)
{
	struct dma_slave_config *config = &idma64c->config;
	unsigned int i = desc->ndesc;
	struct idma64_hw_desc *hw = &desc->hw[i - 1];
	struct idma64_lli *lli = hw->lli;
	u64 llp = 0;

	/* Fill the hardware descriptors and link them to a list */
	do {
		hw = &desc->hw[--i];
		idma64_hw_desc_fill(hw, config, desc->direction, llp);
		llp = hw->llp;
		desc->length += hw->len;
	} while (i);

	/* Trigger an interrupt after the last block is transfered */
	lli->ctllo |= IDMA64C_CTLL_INT_EN;

	/* Disable LLP transfer in the last block */
	lli->ctllo &= ~(IDMA64C_CTLL_LLP_S_EN | IDMA64C_CTLL_LLP_D_EN);
}