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
struct dvb_usb_device {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  info (char*) ; 
 int /*<<< orphan*/  lme2510_usb_talk (struct dvb_usb_device*,int*,int,int*,int) ; 

__attribute__((used)) static void lme_coldreset(struct dvb_usb_device *d)
{
	u8 data[1] = {0};
	data[0] = 0x0a;
	info("FRM Firmware Cold Reset");

	lme2510_usb_talk(d, data, sizeof(data), data, sizeof(data));

	return;
}