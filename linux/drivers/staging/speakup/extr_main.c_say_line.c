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
typedef  int /*<<< orphan*/  u_short ;
typedef  scalar_t__ u16 ;
struct vc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_BLANK ; 
 scalar_t__ SAY_LINE_INDENT ; 
 scalar_t__ SPACE ; 
 scalar_t__* buf ; 
 int get_line (struct vc_data*) ; 
 int spk_msg_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spk_punc_mask ; 
 int /*<<< orphan*/ * spk_punc_masks ; 
 size_t spk_reading_punc ; 
 int /*<<< orphan*/  spkup_write (scalar_t__*,int) ; 
 int /*<<< orphan*/  synth_printf (char*,int) ; 
 scalar_t__ this_speakup_key ; 

__attribute__((used)) static void say_line(struct vc_data *vc)
{
	int i = get_line(vc);
	u16 *cp;
	u_short saved_punc_mask = spk_punc_mask;

	if (i == 0) {
		synth_printf("%s\n", spk_msg_get(MSG_BLANK));
		return;
	}
	buf[i++] = '\n';
	if (this_speakup_key == SAY_LINE_INDENT) {
		cp = buf;
		while (*cp == SPACE)
			cp++;
		synth_printf("%zd, ", (cp - buf) + 1);
	}
	spk_punc_mask = spk_punc_masks[spk_reading_punc];
	spkup_write(buf, i);
	spk_punc_mask = saved_punc_mask;
}