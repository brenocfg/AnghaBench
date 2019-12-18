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
struct vc_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ MSG_BRIGHT ; 
 scalar_t__ MSG_COLORS_START ; 
 scalar_t__ MSG_ON ; 
 scalar_t__ MSG_ON_BLINKING ; 
 int spk_attr ; 
 int /*<<< orphan*/  spk_msg_get (scalar_t__) ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void say_attributes(struct vc_data *vc)
{
	int fg = spk_attr & 0x0f;
	int bg = spk_attr >> 4;

	if (fg > 8) {
		synth_printf("%s ", spk_msg_get(MSG_BRIGHT));
		fg -= 8;
	}
	synth_printf("%s", spk_msg_get(MSG_COLORS_START + fg));
	if (bg > 7) {
		synth_printf(" %s ", spk_msg_get(MSG_ON_BLINKING));
		bg -= 8;
	} else {
		synth_printf(" %s ", spk_msg_get(MSG_ON));
	}
	synth_printf("%s\n", spk_msg_get(MSG_COLORS_START + bg));
}