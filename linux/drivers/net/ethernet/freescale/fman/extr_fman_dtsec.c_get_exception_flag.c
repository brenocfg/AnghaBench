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
 int DTSEC_IMASK_BREN ; 
 int DTSEC_IMASK_BTEN ; 
 int DTSEC_IMASK_CRLEN ; 
 int DTSEC_IMASK_GRSCEN ; 
 int DTSEC_IMASK_GTSCEN ; 
 int DTSEC_IMASK_LCEN ; 
 int DTSEC_IMASK_MAGEN ; 
 int DTSEC_IMASK_MMRDEN ; 
 int DTSEC_IMASK_MMWREN ; 
 int DTSEC_IMASK_MSROEN ; 
 int DTSEC_IMASK_RXCEN ; 
 int DTSEC_IMASK_TDPEEN ; 
 int DTSEC_IMASK_TXCEN ; 
 int DTSEC_IMASK_TXEEN ; 
 int DTSEC_IMASK_XFUNEN ; 
#define  FM_MAC_EX_1G_BAB_RX 142 
#define  FM_MAC_EX_1G_BAB_TX 141 
#define  FM_MAC_EX_1G_COL_RET_LMT 140 
#define  FM_MAC_EX_1G_DATA_ERR 139 
#define  FM_MAC_EX_1G_GRATEFUL_RX_STP_COMPLET 138 
#define  FM_MAC_EX_1G_GRATEFUL_TX_STP_COMPLET 137 
#define  FM_MAC_EX_1G_LATE_COL 136 
#define  FM_MAC_EX_1G_MAG_PCKT 135 
#define  FM_MAC_EX_1G_MII_MNG_RD_COMPLET 134 
#define  FM_MAC_EX_1G_MII_MNG_WR_COMPLET 133 
#define  FM_MAC_EX_1G_RX_CTL 132 
#define  FM_MAC_EX_1G_RX_MIB_CNT_OVFL 131 
#define  FM_MAC_EX_1G_TX_CTL 130 
#define  FM_MAC_EX_1G_TX_ERR 129 
#define  FM_MAC_EX_1G_TX_FIFO_UNDRN 128 

__attribute__((used)) static int get_exception_flag(enum fman_mac_exceptions exception)
{
	u32 bit_mask;

	switch (exception) {
	case FM_MAC_EX_1G_BAB_RX:
		bit_mask = DTSEC_IMASK_BREN;
		break;
	case FM_MAC_EX_1G_RX_CTL:
		bit_mask = DTSEC_IMASK_RXCEN;
		break;
	case FM_MAC_EX_1G_GRATEFUL_TX_STP_COMPLET:
		bit_mask = DTSEC_IMASK_GTSCEN;
		break;
	case FM_MAC_EX_1G_BAB_TX:
		bit_mask = DTSEC_IMASK_BTEN;
		break;
	case FM_MAC_EX_1G_TX_CTL:
		bit_mask = DTSEC_IMASK_TXCEN;
		break;
	case FM_MAC_EX_1G_TX_ERR:
		bit_mask = DTSEC_IMASK_TXEEN;
		break;
	case FM_MAC_EX_1G_LATE_COL:
		bit_mask = DTSEC_IMASK_LCEN;
		break;
	case FM_MAC_EX_1G_COL_RET_LMT:
		bit_mask = DTSEC_IMASK_CRLEN;
		break;
	case FM_MAC_EX_1G_TX_FIFO_UNDRN:
		bit_mask = DTSEC_IMASK_XFUNEN;
		break;
	case FM_MAC_EX_1G_MAG_PCKT:
		bit_mask = DTSEC_IMASK_MAGEN;
		break;
	case FM_MAC_EX_1G_MII_MNG_RD_COMPLET:
		bit_mask = DTSEC_IMASK_MMRDEN;
		break;
	case FM_MAC_EX_1G_MII_MNG_WR_COMPLET:
		bit_mask = DTSEC_IMASK_MMWREN;
		break;
	case FM_MAC_EX_1G_GRATEFUL_RX_STP_COMPLET:
		bit_mask = DTSEC_IMASK_GRSCEN;
		break;
	case FM_MAC_EX_1G_DATA_ERR:
		bit_mask = DTSEC_IMASK_TDPEEN;
		break;
	case FM_MAC_EX_1G_RX_MIB_CNT_OVFL:
		bit_mask = DTSEC_IMASK_MSROEN;
		break;
	default:
		bit_mask = 0;
		break;
	}

	return bit_mask;
}