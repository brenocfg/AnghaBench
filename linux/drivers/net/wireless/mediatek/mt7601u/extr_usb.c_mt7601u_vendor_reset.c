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
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_VEND_DEV_MODE ; 
 int /*<<< orphan*/  MT_VEND_DEV_MODE_RESET ; 
 int /*<<< orphan*/  USB_DIR_OUT ; 
 int /*<<< orphan*/  mt7601u_vendor_request (struct mt7601u_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void mt7601u_vendor_reset(struct mt7601u_dev *dev)
{
	mt7601u_vendor_request(dev, MT_VEND_DEV_MODE, USB_DIR_OUT,
			       MT_VEND_DEV_MODE_RESET, 0, NULL, 0);
}