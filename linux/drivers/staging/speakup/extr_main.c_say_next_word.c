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
typedef  scalar_t__ u_short ;
typedef  int /*<<< orphan*/  u_char ;
typedef  int u16 ;
struct vc_data {int vc_cols; int vc_rows; } ;

/* Variables and functions */
 scalar_t__ IS_WDLM (int) ; 
 int SPACE ; 
 int /*<<< orphan*/  announce_edge (struct vc_data*,scalar_t__) ; 
 scalar_t__ edge_bottom ; 
 scalar_t__ edge_right ; 
 int get_char (struct vc_data*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  say_word (struct vc_data*) ; 
 int spk_parked ; 
 scalar_t__ spk_pos ; 
 int spk_x ; 
 int spk_y ; 

__attribute__((used)) static void say_next_word(struct vc_data *vc)
{
	u_char temp;
	u16 ch;
	u_short edge_said = 0, last_state = 2, state = 0;

	spk_parked |= 0x01;
	if (spk_x == vc->vc_cols - 1 && spk_y == vc->vc_rows - 1) {
		announce_edge(vc, edge_bottom);
		return;
	}
	while (1) {
		ch = get_char(vc, (u_short *)spk_pos, &temp);
		if (ch == SPACE || ch == 0)
			state = 0;
		else if (ch < 0x100 && IS_WDLM(ch))
			state = 1;
		else
			state = 2;
		if (state > last_state)
			break;
		if (spk_x >= vc->vc_cols - 1) {
			if (spk_y == vc->vc_rows - 1) {
				edge_said = edge_bottom;
				break;
			}
			state = 0;
			spk_y++;
			spk_x = 0;
			edge_said = edge_right;
		} else {
			spk_x++;
		}
		spk_pos += 2;
		last_state = state;
	}
	if (edge_said > 0)
		announce_edge(vc, edge_said);
	say_word(vc);
}