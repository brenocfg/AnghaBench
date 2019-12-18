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
struct ar9170 {int dummy; } ;

/* Variables and functions */
 int AR9170_MAC_FCS_FIFO_PROT ; 
 int AR9170_MAC_FTF_DEFAULTS ; 
 int AR9170_MAC_FTF_MONITOR ; 
 int AR9170_MAC_REG_ACK_EXTENSION ; 
 int AR9170_MAC_REG_ACK_TPC ; 
 int AR9170_MAC_REG_AMPDU_DENSITY ; 
 int AR9170_MAC_REG_AMPDU_FACTOR ; 
 int AR9170_MAC_REG_AMPDU_RX_THRESH ; 
 int AR9170_MAC_REG_BACKOFF_PROTECT ; 
 int AR9170_MAC_REG_BASIC_RATE ; 
 int AR9170_MAC_REG_BCN_HT1 ; 
 int AR9170_MAC_REG_BCN_PERIOD ; 
 int AR9170_MAC_REG_EIFS_AND_SIFS ; 
 int AR9170_MAC_REG_FCS_SELECT ; 
 int AR9170_MAC_REG_FRAMETYPE_FILTER ; 
 int AR9170_MAC_REG_GROUP_HASH_TBL_H ; 
 int AR9170_MAC_REG_GROUP_HASH_TBL_L ; 
 int AR9170_MAC_REG_MANDATORY_RATE ; 
 int AR9170_MAC_REG_MISC_680 ; 
 int AR9170_MAC_REG_PRETBTT ; 
 int AR9170_MAC_REG_RETRY_MAX ; 
 int AR9170_MAC_REG_RTS_CTS_RATE ; 
 int AR9170_MAC_REG_RX_CONTROL ; 
 int AR9170_MAC_REG_RX_PE_DELAY ; 
 int AR9170_MAC_REG_RX_THRESHOLD ; 
 int AR9170_MAC_REG_RX_TIMEOUT ; 
 int AR9170_MAC_REG_SLOT_TIME ; 
 int AR9170_MAC_REG_SNIFFER ; 
 int AR9170_MAC_REG_TID_CFACK_CFEND_RATE ; 
 int AR9170_MAC_REG_TXOP_DURATION ; 
 int AR9170_MAC_REG_TXOP_NOT_ENOUGH_IND ; 
 int AR9170_MAC_REG_TXRX_MPI ; 
 int AR9170_MAC_RX_CTRL_DEAGG ; 
 int AR9170_MAC_RX_CTRL_SHORT_FILTER ; 
 int AR9170_MAC_SNIFFER_DEFAULTS ; 
 int /*<<< orphan*/  carl9170_regwrite (int,int) ; 
 int /*<<< orphan*/  carl9170_regwrite_begin (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite_finish () ; 
 int carl9170_regwrite_result () ; 

int carl9170_init_mac(struct ar9170 *ar)
{
	carl9170_regwrite_begin(ar);

	/* switch MAC to OTUS interface */
	carl9170_regwrite(0x1c3600, 0x3);

	carl9170_regwrite(AR9170_MAC_REG_ACK_EXTENSION, 0x40);

	carl9170_regwrite(AR9170_MAC_REG_RETRY_MAX, 0x0);

	carl9170_regwrite(AR9170_MAC_REG_FRAMETYPE_FILTER,
			  AR9170_MAC_FTF_MONITOR);

	/* enable MMIC */
	carl9170_regwrite(AR9170_MAC_REG_SNIFFER,
			AR9170_MAC_SNIFFER_DEFAULTS);

	carl9170_regwrite(AR9170_MAC_REG_RX_THRESHOLD, 0xc1f80);

	carl9170_regwrite(AR9170_MAC_REG_RX_PE_DELAY, 0x70);
	carl9170_regwrite(AR9170_MAC_REG_EIFS_AND_SIFS, 0xa144000);
	carl9170_regwrite(AR9170_MAC_REG_SLOT_TIME, 9 << 10);

	/* CF-END & CF-ACK rate => 24M OFDM */
	carl9170_regwrite(AR9170_MAC_REG_TID_CFACK_CFEND_RATE, 0x59900000);

	/* NAV protects ACK only (in TXOP) */
	carl9170_regwrite(AR9170_MAC_REG_TXOP_DURATION, 0x201);

	/* Set Beacon PHY CTRL's TPC to 0x7, TA1=1 */
	/* OTUS set AM to 0x1 */
	carl9170_regwrite(AR9170_MAC_REG_BCN_HT1, 0x8000170);

	carl9170_regwrite(AR9170_MAC_REG_BACKOFF_PROTECT, 0x105);

	/* Aggregation MAX number and timeout */
	carl9170_regwrite(AR9170_MAC_REG_AMPDU_FACTOR, 0x8000a);
	carl9170_regwrite(AR9170_MAC_REG_AMPDU_DENSITY, 0x140a07);

	carl9170_regwrite(AR9170_MAC_REG_FRAMETYPE_FILTER,
			  AR9170_MAC_FTF_DEFAULTS);

	carl9170_regwrite(AR9170_MAC_REG_RX_CONTROL,
			  AR9170_MAC_RX_CTRL_DEAGG |
			  AR9170_MAC_RX_CTRL_SHORT_FILTER);

	/* rate sets */
	carl9170_regwrite(AR9170_MAC_REG_BASIC_RATE, 0x150f);
	carl9170_regwrite(AR9170_MAC_REG_MANDATORY_RATE, 0x150f);
	carl9170_regwrite(AR9170_MAC_REG_RTS_CTS_RATE, 0x0030033);

	/* MIMO response control */
	carl9170_regwrite(AR9170_MAC_REG_ACK_TPC, 0x4003c1e);

	carl9170_regwrite(AR9170_MAC_REG_AMPDU_RX_THRESH, 0xffff);

	/* set PHY register read timeout (??) */
	carl9170_regwrite(AR9170_MAC_REG_MISC_680, 0xf00008);

	/* Disable Rx TimeOut, workaround for BB. */
	carl9170_regwrite(AR9170_MAC_REG_RX_TIMEOUT, 0x0);

	/* Set WLAN DMA interrupt mode: generate int per packet */
	carl9170_regwrite(AR9170_MAC_REG_TXRX_MPI, 0x110011);

	carl9170_regwrite(AR9170_MAC_REG_FCS_SELECT,
			AR9170_MAC_FCS_FIFO_PROT);

	/* Disables the CF_END frame, undocumented register */
	carl9170_regwrite(AR9170_MAC_REG_TXOP_NOT_ENOUGH_IND,
			0x141e0f48);

	/* reset group hash table */
	carl9170_regwrite(AR9170_MAC_REG_GROUP_HASH_TBL_L, 0xffffffff);
	carl9170_regwrite(AR9170_MAC_REG_GROUP_HASH_TBL_H, 0xffffffff);

	/* disable PRETBTT interrupt */
	carl9170_regwrite(AR9170_MAC_REG_PRETBTT, 0x0);
	carl9170_regwrite(AR9170_MAC_REG_BCN_PERIOD, 0x0);

	carl9170_regwrite_finish();

	return carl9170_regwrite_result();
}