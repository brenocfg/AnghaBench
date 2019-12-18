#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  urb; } ;
struct TYPE_3__ {TYPE_2__ resp; } ;
struct mt7601u_dev {TYPE_1__ mcu; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7601u_usb_free_buf (struct mt7601u_dev*,TYPE_2__*) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

void mt7601u_mcu_cmd_deinit(struct mt7601u_dev *dev)
{
	usb_kill_urb(dev->mcu.resp.urb);
	mt7601u_usb_free_buf(dev, &dev->mcu.resp);
}