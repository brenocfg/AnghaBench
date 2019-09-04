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
struct TYPE_2__ {int /*<<< orphan*/  tx_spoof_check_err; int /*<<< orphan*/  tx_dma_err; int /*<<< orphan*/  tx_hdr_parse_err; } ;

/* Variables and functions */
#define  BE_TX_COMP_ACL_ERR 130 
#define  BE_TX_COMP_HDR_PARSE_ERR 129 
#define  BE_TX_COMP_NDMA_ERR 128 
 TYPE_1__* tx_stats (struct be_tx_obj*) ; 

__attribute__((used)) static inline void be_update_tx_err(struct be_tx_obj *txo, u8 status)
{
	switch (status) {
	case BE_TX_COMP_HDR_PARSE_ERR:
		tx_stats(txo)->tx_hdr_parse_err++;
		break;
	case BE_TX_COMP_NDMA_ERR:
		tx_stats(txo)->tx_dma_err++;
		break;
	case BE_TX_COMP_ACL_ERR:
		tx_stats(txo)->tx_spoof_check_err++;
		break;
	}
}