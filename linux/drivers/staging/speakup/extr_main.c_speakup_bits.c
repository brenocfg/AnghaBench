#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int dummy; } ;
struct TYPE_3__ {char* name; } ;

/* Variables and functions */
 int FIRST_EDIT_BITS ; 
 int /*<<< orphan*/  MSG_EDIT_PROMPT ; 
 int /*<<< orphan*/  MSG_ERROR ; 
 scalar_t__ edit_bits ; 
 TYPE_1__* pb_edit ; 
 char* spk_msg_get (int /*<<< orphan*/ ) ; 
 TYPE_1__* spk_punc_info ; 
 scalar_t__ spk_special_handler ; 
 int /*<<< orphan*/  synth_printf (char*,char*) ; 
 int this_speakup_key ; 

__attribute__((used)) static void speakup_bits(struct vc_data *vc)
{
	int val = this_speakup_key - (FIRST_EDIT_BITS - 1);

	if (spk_special_handler || val < 1 || val > 6) {
		synth_printf("%s\n", spk_msg_get(MSG_ERROR));
		return;
	}
	pb_edit = &spk_punc_info[val];
	synth_printf(spk_msg_get(MSG_EDIT_PROMPT), pb_edit->name);
	spk_special_handler = edit_bits;
}