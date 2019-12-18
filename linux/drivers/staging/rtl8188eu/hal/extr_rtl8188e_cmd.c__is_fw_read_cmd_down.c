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
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  REG_HMETFR ; 
 int usb_read8 (struct adapter*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 _is_fw_read_cmd_down(struct adapter *adapt, u8 msgbox_num)
{
	u8 read_down = false;
	int retry_cnts = 100;

	u8 valid;

	do {
		valid = usb_read8(adapt, REG_HMETFR) & BIT(msgbox_num);
		if (valid == 0)
			read_down = true;
	} while ((!read_down) && (retry_cnts--));

	return read_down;
}