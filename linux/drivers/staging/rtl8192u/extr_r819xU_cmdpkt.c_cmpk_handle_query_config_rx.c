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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct cmpk_query_cfg {int cfg_action; int cfg_type; int cfg_size; int cfg_page; int cfg_offset; int value; int mask; } ;

/* Variables and functions */

__attribute__((used)) static void cmpk_handle_query_config_rx(struct net_device *dev, u8 *pmsg)
{
	struct cmpk_query_cfg	rx_query_cfg;

	/* 1. Extract TX feedback info from RFD to temp structure buffer. */
	/* It seems that FW use big endian(MIPS) and DRV use little endian in
	 * windows OS. So we have to read the content byte by byte or transfer
	 * endian type before copy the message copy.
	 */
	rx_query_cfg.cfg_action		= (pmsg[4] & 0x80) >> 7;
	rx_query_cfg.cfg_type		= (pmsg[4] & 0x60) >> 5;
	rx_query_cfg.cfg_size		= (pmsg[4] & 0x18) >> 3;
	rx_query_cfg.cfg_page		= (pmsg[6] & 0x0F) >> 0;
	rx_query_cfg.cfg_offset		= pmsg[7];
	rx_query_cfg.value		= (pmsg[8]  << 24) | (pmsg[9]  << 16) |
					  (pmsg[10] <<  8) | (pmsg[11] <<  0);
	rx_query_cfg.mask		= (pmsg[12] << 24) | (pmsg[13] << 16) |
					  (pmsg[14] <<  8) | (pmsg[15] <<  0);
}