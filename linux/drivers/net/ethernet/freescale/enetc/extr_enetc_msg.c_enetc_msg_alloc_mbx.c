#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct enetc_hw {int dummy; } ;
struct enetc_si {struct enetc_hw hw; TYPE_1__* pdev; } ;
struct enetc_pf {struct enetc_msg_swbd* rxmsg; } ;
struct enetc_msg_swbd {int /*<<< orphan*/  dma; int /*<<< orphan*/  size; int /*<<< orphan*/  vaddr; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_DEFAULT_MSG_SIZE ; 
 int /*<<< orphan*/  ENETC_PSIVMSGRCVAR0 (int) ; 
 int /*<<< orphan*/  ENETC_PSIVMSGRCVAR1 (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct enetc_pf* enetc_si_priv (struct enetc_si*) ; 
 int /*<<< orphan*/  enetc_wr (struct enetc_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enetc_msg_alloc_mbx(struct enetc_si *si, int idx)
{
	struct enetc_pf *pf = enetc_si_priv(si);
	struct device *dev = &si->pdev->dev;
	struct enetc_hw *hw = &si->hw;
	struct enetc_msg_swbd *msg;
	u32 val;

	msg = &pf->rxmsg[idx];
	/* allocate and set receive buffer */
	msg->size = ENETC_DEFAULT_MSG_SIZE;

	msg->vaddr = dma_alloc_coherent(dev, msg->size, &msg->dma,
					GFP_KERNEL);
	if (!msg->vaddr) {
		dev_err(dev, "msg: fail to alloc dma buffer of size: %d\n",
			msg->size);
		return -ENOMEM;
	}

	/* set multiple of 32 bytes */
	val = lower_32_bits(msg->dma);
	enetc_wr(hw, ENETC_PSIVMSGRCVAR0(idx), val);
	val = upper_32_bits(msg->dma);
	enetc_wr(hw, ENETC_PSIVMSGRCVAR1(idx), val);

	return 0;
}