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
typedef  scalar_t__ u16 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ MAX_RX_DMA_BUFFER_SIZE_88E ; 
 scalar_t__ REG_TRXFF_BNDY ; 
 int /*<<< orphan*/  usb_write16 (struct adapter*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void _InitPageBoundary(struct adapter *Adapter)
{
	/*  RX Page Boundary */
	/*  */
	u16 rxff_bndy = MAX_RX_DMA_BUFFER_SIZE_88E - 1;

	usb_write16(Adapter, (REG_TRXFF_BNDY + 2), rxff_bndy);
}