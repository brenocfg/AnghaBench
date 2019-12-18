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
 int /*<<< orphan*/  MSG_HEY_THATS_BETTER ; 
 int /*<<< orphan*/  MSG_YOU_TURNED_ME_OFF ; 
 int /*<<< orphan*/  speakup_date (struct vc_data*) ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 int spk_shut_up ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void speakup_off(struct vc_data *vc)
{
	if (spk_shut_up & 0x80) {
		spk_shut_up &= 0x7f;
		synth_printf("%s\n", spk_msg_get(MSG_HEY_THATS_BETTER));
	} else {
		spk_shut_up |= 0x80;
		synth_printf("%s\n", spk_msg_get(MSG_YOU_TURNED_ME_OFF));
	}
	speakup_date(vc);
}