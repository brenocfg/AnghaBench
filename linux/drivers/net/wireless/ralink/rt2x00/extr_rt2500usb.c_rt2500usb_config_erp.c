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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00lib_erp {int beacon_int; int /*<<< orphan*/  eifs; int /*<<< orphan*/  sifs; int /*<<< orphan*/  slot_time; int /*<<< orphan*/  basic_rates; int /*<<< orphan*/  short_preamble; } ;
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int BSS_CHANGED_BASIC_RATES ; 
 int BSS_CHANGED_BEACON_INT ; 
 int BSS_CHANGED_ERP_PREAMBLE ; 
 int BSS_CHANGED_ERP_SLOT ; 
 int /*<<< orphan*/  MAC_CSR10 ; 
 int /*<<< orphan*/  MAC_CSR11 ; 
 int /*<<< orphan*/  MAC_CSR12 ; 
 int /*<<< orphan*/  TXRX_CSR10 ; 
 int /*<<< orphan*/  TXRX_CSR10_AUTORESPOND_PREAMBLE ; 
 int /*<<< orphan*/  TXRX_CSR11 ; 
 int /*<<< orphan*/  TXRX_CSR18 ; 
 int /*<<< orphan*/  TXRX_CSR18_INTERVAL ; 
 int /*<<< orphan*/  rt2500usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2500usb_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void rt2500usb_config_erp(struct rt2x00_dev *rt2x00dev,
				 struct rt2x00lib_erp *erp,
				 u32 changed)
{
	u16 reg;

	if (changed & BSS_CHANGED_ERP_PREAMBLE) {
		reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR10);
		rt2x00_set_field16(&reg, TXRX_CSR10_AUTORESPOND_PREAMBLE,
				   !!erp->short_preamble);
		rt2500usb_register_write(rt2x00dev, TXRX_CSR10, reg);
	}

	if (changed & BSS_CHANGED_BASIC_RATES)
		rt2500usb_register_write(rt2x00dev, TXRX_CSR11,
					 erp->basic_rates);

	if (changed & BSS_CHANGED_BEACON_INT) {
		reg = rt2500usb_register_read(rt2x00dev, TXRX_CSR18);
		rt2x00_set_field16(&reg, TXRX_CSR18_INTERVAL,
				   erp->beacon_int * 4);
		rt2500usb_register_write(rt2x00dev, TXRX_CSR18, reg);
	}

	if (changed & BSS_CHANGED_ERP_SLOT) {
		rt2500usb_register_write(rt2x00dev, MAC_CSR10, erp->slot_time);
		rt2500usb_register_write(rt2x00dev, MAC_CSR11, erp->sifs);
		rt2500usb_register_write(rt2x00dev, MAC_CSR12, erp->eifs);
	}
}