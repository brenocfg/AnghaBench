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
typedef  int /*<<< orphan*/  u16 ;
struct usbnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCS7830_WR_BMREQ ; 
 int /*<<< orphan*/  MCS7830_WR_BREQ ; 
 int /*<<< orphan*/  usbnet_write_cmd_async (struct usbnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcs7830_set_reg_async(struct usbnet *dev, u16 index, u16 size, void *data)
{
	usbnet_write_cmd_async(dev, MCS7830_WR_BREQ, MCS7830_WR_BMREQ,
				0x0000, index, data, size);
}