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
typedef  int u32 ;
typedef  size_t u16 ;
struct qtnf_pearl_rx_bd {int /*<<< orphan*/  info; } ;
struct TYPE_2__ {size_t rx_bd_r_index; } ;
struct qtnf_pcie_pearl_state {struct qtnf_pearl_rx_bd* rx_bd_vbase; TYPE_1__ base; } ;

/* Variables and functions */
 int QTN_TXDONE_MASK ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qtnf_rx_data_ready(struct qtnf_pcie_pearl_state *ps)
{
	u16 index = ps->base.rx_bd_r_index;
	struct qtnf_pearl_rx_bd *rxbd;
	u32 descw;

	rxbd = &ps->rx_bd_vbase[index];
	descw = le32_to_cpu(rxbd->info);

	if (descw & QTN_TXDONE_MASK)
		return 1;

	return 0;
}