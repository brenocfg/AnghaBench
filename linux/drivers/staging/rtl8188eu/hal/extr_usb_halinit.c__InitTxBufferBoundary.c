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
typedef  int /*<<< orphan*/  u8 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ REG_TDECTRL ; 
 scalar_t__ REG_TRXFF_BNDY ; 
 scalar_t__ REG_TXPKTBUF_BCNQ_BDNY ; 
 scalar_t__ REG_TXPKTBUF_MGQ_BDNY ; 
 scalar_t__ REG_TXPKTBUF_WMAC_LBK_BF_HD ; 
 int /*<<< orphan*/  usb_write8 (struct adapter*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _InitTxBufferBoundary(struct adapter *Adapter, u8 txpktbuf_bndy)
{
	usb_write8(Adapter, REG_TXPKTBUF_BCNQ_BDNY, txpktbuf_bndy);
	usb_write8(Adapter, REG_TXPKTBUF_MGQ_BDNY, txpktbuf_bndy);
	usb_write8(Adapter, REG_TXPKTBUF_WMAC_LBK_BF_HD, txpktbuf_bndy);
	usb_write8(Adapter, REG_TRXFF_BNDY, txpktbuf_bndy);
	usb_write8(Adapter, REG_TDECTRL + 1, txpktbuf_bndy);
}