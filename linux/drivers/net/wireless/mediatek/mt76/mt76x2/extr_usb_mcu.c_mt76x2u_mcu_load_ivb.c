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
struct mt76x02_dev {int /*<<< orphan*/  mt76; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_VEND_DEV_MODE ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  mt76u_vendor_request (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt76x2u_mcu_load_ivb(struct mt76x02_dev *dev)
{
	mt76u_vendor_request(&dev->mt76, MT_VEND_DEV_MODE,
			     USB_DIR_OUT | USB_TYPE_VENDOR,
			     0x12, 0, NULL, 0);
}