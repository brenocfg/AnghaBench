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
typedef  int u8 ;
struct be_tx_obj {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_sge_err; int /*<<< orphan*/  tx_dma_err; int /*<<< orphan*/  tx_internal_parity_err; int /*<<< orphan*/  tx_qinq_err; int /*<<< orphan*/  tx_spoof_check_err; int /*<<< orphan*/  tx_tso_err; } ;

/* Variables and functions */
#define  LANCER_TX_COMP_DMA_ERR 134 
#define  LANCER_TX_COMP_HSW_DROP_MAC_ERR 133 
#define  LANCER_TX_COMP_HSW_DROP_VLAN_ERR 132 
#define  LANCER_TX_COMP_LSO_ERR 131 
#define  LANCER_TX_COMP_PARITY_ERR 130 
#define  LANCER_TX_COMP_QINQ_ERR 129 
#define  LANCER_TX_COMP_SGE_ERR 128 
 TYPE_1__* tx_stats (struct be_tx_obj*) ; 

__attribute__((used)) static inline void lancer_update_tx_err(struct be_tx_obj *txo, u8 status)
{
	switch (status) {
	case LANCER_TX_COMP_LSO_ERR:
		tx_stats(txo)->tx_tso_err++;
		break;
	case LANCER_TX_COMP_HSW_DROP_MAC_ERR:
	case LANCER_TX_COMP_HSW_DROP_VLAN_ERR:
		tx_stats(txo)->tx_spoof_check_err++;
		break;
	case LANCER_TX_COMP_QINQ_ERR:
		tx_stats(txo)->tx_qinq_err++;
		break;
	case LANCER_TX_COMP_PARITY_ERR:
		tx_stats(txo)->tx_internal_parity_err++;
		break;
	case LANCER_TX_COMP_DMA_ERR:
		tx_stats(txo)->tx_dma_err++;
		break;
	case LANCER_TX_COMP_SGE_ERR:
		tx_stats(txo)->tx_sge_err++;
		break;
	}
}