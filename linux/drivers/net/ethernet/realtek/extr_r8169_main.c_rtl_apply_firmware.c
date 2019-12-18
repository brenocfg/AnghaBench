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
struct rtl8169_private {scalar_t__ rtl_fw; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl_fw_write_firmware (struct rtl8169_private*,scalar_t__) ; 

__attribute__((used)) static void rtl_apply_firmware(struct rtl8169_private *tp)
{
	/* TODO: release firmware if rtl_fw_write_firmware signals failure. */
	if (tp->rtl_fw)
		rtl_fw_write_firmware(tp, tp->rtl_fw);
}