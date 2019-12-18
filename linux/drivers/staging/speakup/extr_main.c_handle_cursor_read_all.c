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
#define  RA_DOWN_ARROW 135 
#define  RA_FIND_NEXT_SENT 134 
#define  RA_FIND_PREV_SENT 133 
#define  RA_NEXT_LINE 132 
#define  RA_NEXT_SENT 131 
#define  RA_PREV_LINE 130 
#define  RA_PREV_SENT 129 
#define  RA_TIMER 128 
 int get_sentence_buf (struct vc_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_fakekey2 (struct vc_data*,int const) ; 
 int /*<<< orphan*/  read_all_doc (struct vc_data*) ; 
 int /*<<< orphan*/  say_sentence_num (int,int) ; 
 int /*<<< orphan*/  spk_get_index_count (int*,int*) ; 
 int /*<<< orphan*/  spk_reset_index_count (int) ; 
 int /*<<< orphan*/  start_read_all_timer (struct vc_data*,int const) ; 
 int /*<<< orphan*/  synth_insert_next_index (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_cursor_read_all(struct vc_data *vc, int command)
{
	int indcount, sentcount, rv, sn;

	switch (command) {
	case RA_NEXT_SENT:
		/* Get Current Sentence */
		spk_get_index_count(&indcount, &sentcount);
		/*printk("%d %d  ", indcount, sentcount); */
		spk_reset_index_count(sentcount + 1);
		if (indcount == 1) {
			if (!say_sentence_num(sentcount + 1, 0)) {
				kbd_fakekey2(vc, RA_FIND_NEXT_SENT);
				return;
			}
			synth_insert_next_index(0);
		} else {
			sn = 0;
			if (!say_sentence_num(sentcount + 1, 1)) {
				sn = 1;
				spk_reset_index_count(sn);
			} else {
				synth_insert_next_index(0);
			}
			if (!say_sentence_num(sn, 0)) {
				kbd_fakekey2(vc, RA_FIND_NEXT_SENT);
				return;
			}
			synth_insert_next_index(0);
		}
		start_read_all_timer(vc, RA_TIMER);
		break;
	case RA_PREV_SENT:
		break;
	case RA_NEXT_LINE:
		read_all_doc(vc);
		break;
	case RA_PREV_LINE:
		break;
	case RA_DOWN_ARROW:
		if (get_sentence_buf(vc, 0) == -1) {
			kbd_fakekey2(vc, RA_DOWN_ARROW);
		} else {
			say_sentence_num(0, 0);
			synth_insert_next_index(0);
			start_read_all_timer(vc, RA_TIMER);
		}
		break;
	case RA_FIND_NEXT_SENT:
		rv = get_sentence_buf(vc, 0);
		if (rv == -1)
			read_all_doc(vc);
		if (rv == 0) {
			kbd_fakekey2(vc, RA_FIND_NEXT_SENT);
		} else {
			say_sentence_num(1, 0);
			synth_insert_next_index(0);
			start_read_all_timer(vc, RA_TIMER);
		}
		break;
	case RA_FIND_PREV_SENT:
		break;
	case RA_TIMER:
		spk_get_index_count(&indcount, &sentcount);
		if (indcount < 2)
			kbd_fakekey2(vc, RA_DOWN_ARROW);
		else
			start_read_all_timer(vc, RA_TIMER);
		break;
	}
}