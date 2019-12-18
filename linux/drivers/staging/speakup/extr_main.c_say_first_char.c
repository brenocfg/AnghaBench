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
typedef  scalar_t__ u16 ;
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_BLANK ; 
 scalar_t__ SPACE ; 
 scalar_t__* buf ; 
 int get_line (struct vc_data*) ; 
 int /*<<< orphan*/  speak_char (scalar_t__) ; 
 int spk_msg_get (int /*<<< orphan*/ ) ; 
 int spk_parked ; 
 int spk_pos ; 
 int spk_x ; 
 int /*<<< orphan*/  synth_printf (char*,int) ; 

__attribute__((used)) static void say_first_char(struct vc_data *vc)
{
	int i, len = get_line(vc);
	u16 ch;

	spk_parked |= 0x01;
	if (len == 0) {
		synth_printf("%s\n", spk_msg_get(MSG_BLANK));
		return;
	}
	for (i = 0; i < len; i++)
		if (buf[i] != SPACE)
			break;
	ch = buf[i];
	spk_pos -= (spk_x - i) * 2;
	spk_x = i;
	synth_printf("%d, ", ++i);
	speak_char(ch);
}