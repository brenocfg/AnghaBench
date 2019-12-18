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
typedef  scalar_t__ u_char ;
typedef  scalar_t__ u16 ;
struct vc_data {int vc_cols; int vc_rows; int vc_size_row; scalar_t__ vc_origin; } ;

/* Variables and functions */
 scalar_t__ KT_LATIN ; 
 scalar_t__ KT_SPKUP ; 
 int /*<<< orphan*/  MSG_GOTO_CANCELED ; 
 scalar_t__ SPEAKUP_GOTO ; 
 int goto_pos ; 
 int goto_x ; 
 int /*<<< orphan*/  say_line (struct vc_data*) ; 
 int /*<<< orphan*/  say_word (struct vc_data*) ; 
 int simple_strtoul (scalar_t__*,char**,int) ; 
 int /*<<< orphan*/  spk_killed ; 
 int /*<<< orphan*/  spk_msg_get (int /*<<< orphan*/ ) ; 
 int spk_parked ; 
 scalar_t__ spk_pos ; 
 int /*<<< orphan*/ * spk_special_handler ; 
 int spk_x ; 
 int spk_y ; 
 int /*<<< orphan*/  spkup_write (scalar_t__*,int) ; 
 int /*<<< orphan*/  synth_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_goto(struct vc_data *vc, u_char type, u_char ch, u_short key)
{
	static u_char goto_buf[8];
	static int num;
	int maxlen;
	char *cp;
	u16 wch;

	if (type == KT_SPKUP && ch == SPEAKUP_GOTO)
		goto do_goto;
	if (type == KT_LATIN && ch == '\n')
		goto do_goto;
	if (type != 0)
		goto oops;
	if (ch == 8) {
		u16 wch;

		if (num == 0)
			return -1;
		wch = goto_buf[--num];
		goto_buf[num] = '\0';
		spkup_write(&wch, 1);
		return 1;
	}
	if (ch < '+' || ch > 'y')
		goto oops;
	wch = ch;
	goto_buf[num++] = ch;
	goto_buf[num] = '\0';
	spkup_write(&wch, 1);
	maxlen = (*goto_buf >= '0') ? 3 : 4;
	if ((ch == '+' || ch == '-') && num == 1)
		return 1;
	if (ch >= '0' && ch <= '9' && num < maxlen)
		return 1;
	if (num < maxlen - 1 || num > maxlen)
		goto oops;
	if (ch < 'x' || ch > 'y') {
oops:
		if (!spk_killed)
			synth_printf(" %s\n", spk_msg_get(MSG_GOTO_CANCELED));
		goto_buf[num = 0] = '\0';
		spk_special_handler = NULL;
		return 1;
	}

	/* Do not replace with kstrtoul: here we need cp to be updated */
	goto_pos = simple_strtoul(goto_buf, &cp, 10);

	if (*cp == 'x') {
		if (*goto_buf < '0')
			goto_pos += spk_x;
		else if (goto_pos > 0)
			goto_pos--;

		if (goto_pos >= vc->vc_cols)
			goto_pos = vc->vc_cols - 1;
		goto_x = 1;
	} else {
		if (*goto_buf < '0')
			goto_pos += spk_y;
		else if (goto_pos > 0)
			goto_pos--;

		if (goto_pos >= vc->vc_rows)
			goto_pos = vc->vc_rows - 1;
		goto_x = 0;
	}
	goto_buf[num = 0] = '\0';
do_goto:
	spk_special_handler = NULL;
	spk_parked |= 0x01;
	if (goto_x) {
		spk_pos -= spk_x * 2;
		spk_x = goto_pos;
		spk_pos += goto_pos * 2;
		say_word(vc);
	} else {
		spk_y = goto_pos;
		spk_pos = vc->vc_origin + (goto_pos * vc->vc_size_row);
		say_line(vc);
	}
	return 1;
}