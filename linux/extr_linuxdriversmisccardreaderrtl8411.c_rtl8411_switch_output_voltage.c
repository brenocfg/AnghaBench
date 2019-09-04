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
typedef  int /*<<< orphan*/  u8 ;
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPP_ASIC_1V8 ; 
 int /*<<< orphan*/  BPP_TUNED18_SHIFT_8411 ; 
 int rtl8411_do_switch_output_voltage (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8411_switch_output_voltage(struct rtsx_pcr *pcr, u8 voltage)
{
	return rtl8411_do_switch_output_voltage(pcr, voltage,
			BPP_TUNED18_SHIFT_8411, BPP_ASIC_1V8);
}