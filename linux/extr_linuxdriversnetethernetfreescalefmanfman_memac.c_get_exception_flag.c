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
typedef  int u32 ;
typedef  enum fman_mac_exceptions { ____Placeholder_fman_mac_exceptions } fman_mac_exceptions ;

/* Variables and functions */
#define  FM_MAC_EX_10G_RX_ECC_ER 131 
#define  FM_MAC_EX_10G_TX_ECC_ER 130 
#define  FM_MAC_EX_MAGIC_PACKET_INDICATION 129 
#define  FM_MAC_EX_TS_FIFO_ECC_ERR 128 
 int MEMAC_IMASK_MGI ; 
 int MEMAC_IMASK_RECC_ER ; 
 int MEMAC_IMASK_TECC_ER ; 
 int MEMAC_IMASK_TSECC_ER ; 

__attribute__((used)) static int get_exception_flag(enum fman_mac_exceptions exception)
{
	u32 bit_mask;

	switch (exception) {
	case FM_MAC_EX_10G_TX_ECC_ER:
		bit_mask = MEMAC_IMASK_TECC_ER;
		break;
	case FM_MAC_EX_10G_RX_ECC_ER:
		bit_mask = MEMAC_IMASK_RECC_ER;
		break;
	case FM_MAC_EX_TS_FIFO_ECC_ERR:
		bit_mask = MEMAC_IMASK_TSECC_ER;
		break;
	case FM_MAC_EX_MAGIC_PACKET_INDICATION:
		bit_mask = MEMAC_IMASK_MGI;
		break;
	default:
		bit_mask = 0;
		break;
	}

	return bit_mask;
}