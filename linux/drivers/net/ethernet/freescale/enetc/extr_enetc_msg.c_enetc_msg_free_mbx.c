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
struct enetc_hw {int dummy; } ;
struct enetc_si {TYPE_1__* pdev; struct enetc_hw hw; } ;
struct enetc_pf {struct enetc_msg_swbd* rxmsg; } ;
struct enetc_msg_swbd {int /*<<< orphan*/  dma; int /*<<< orphan*/  vaddr; int /*<<< orphan*/  size; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENETC_PSIVMSGRCVAR0 (int) ; 
 int /*<<< orphan*/  ENETC_PSIVMSGRCVAR1 (int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct enetc_pf* enetc_si_priv (struct enetc_si*) ; 
 int /*<<< orphan*/  enetc_wr (struct enetc_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct enetc_msg_swbd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void enetc_msg_free_mbx(struct enetc_si *si, int idx)
{
	struct enetc_pf *pf = enetc_si_priv(si);
	struct enetc_hw *hw = &si->hw;
	struct enetc_msg_swbd *msg;

	msg = &pf->rxmsg[idx];
	dma_free_coherent(&si->pdev->dev, msg->size, msg->vaddr, msg->dma);
	memset(msg, 0, sizeof(*msg));

	enetc_wr(hw, ENETC_PSIVMSGRCVAR0(idx), 0);
	enetc_wr(hw, ENETC_PSIVMSGRCVAR1(idx), 0);
}