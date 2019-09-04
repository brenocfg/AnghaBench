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
struct kvaser_usb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RESET_CHIP ; 
 int kvaser_usb_leaf_send_simple_cmd (struct kvaser_usb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kvaser_usb_leaf_reset_chip(struct kvaser_usb *dev, int channel)
{
	return kvaser_usb_leaf_send_simple_cmd(dev, CMD_RESET_CHIP, channel);
}