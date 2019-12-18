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
struct sisusb_usb_data {int dummy; } ;

/* Variables and functions */
 int GETIREG (int /*<<< orphan*/ ,int,int*) ; 
 int SETIREG (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SISSR ; 

__attribute__((used)) static int sisusb_triggersr16(struct sisusb_usb_data *sisusb, u8 ramtype)
{
	int ret;
	u8 tmp8;

	ret = GETIREG(SISSR, 0x16, &tmp8);
	if (ramtype <= 1) {
		tmp8 &= 0x3f;
		ret |= SETIREG(SISSR, 0x16, tmp8);
		tmp8 |= 0x80;
		ret |= SETIREG(SISSR, 0x16, tmp8);
	} else {
		tmp8 |= 0xc0;
		ret |= SETIREG(SISSR, 0x16, tmp8);
		tmp8 &= 0x0f;
		ret |= SETIREG(SISSR, 0x16, tmp8);
		tmp8 |= 0x80;
		ret |= SETIREG(SISSR, 0x16, tmp8);
		tmp8 &= 0x0f;
		ret |= SETIREG(SISSR, 0x16, tmp8);
		tmp8 |= 0xd0;
		ret |= SETIREG(SISSR, 0x16, tmp8);
		tmp8 &= 0x0f;
		ret |= SETIREG(SISSR, 0x16, tmp8);
		tmp8 |= 0xa0;
		ret |= SETIREG(SISSR, 0x16, tmp8);
	}
	return ret;
}