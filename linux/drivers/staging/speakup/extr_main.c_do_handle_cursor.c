#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_char ;
struct vc_data {size_t vc_num; int /*<<< orphan*/  vc_y; int /*<<< orphan*/  vc_x; int /*<<< orphan*/  vc_pos; } ;
struct TYPE_7__ {int /*<<< orphan*/  value; } ;
struct TYPE_8__ {TYPE_2__ n; } ;
struct var_t {TYPE_3__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  cy; } ;
struct TYPE_10__ {TYPE_1__ ht; } ;
struct TYPE_9__ {int /*<<< orphan*/  spinlock; } ;

/* Variables and functions */
 scalar_t__ CT_Highlight ; 
 scalar_t__ CT_Off ; 
 int /*<<< orphan*/  CURSOR_TIME ; 
 size_t cursor_con ; 
 int /*<<< orphan*/  cursor_timer ; 
 scalar_t__ cursor_track ; 
 scalar_t__ is_cursor ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  old_cursor_pos ; 
 int /*<<< orphan*/  old_cursor_x ; 
 int /*<<< orphan*/  old_cursor_y ; 
 int /*<<< orphan*/  reset_highlight_buffers (struct vc_data*) ; 
 TYPE_5__** speakup_console ; 
 TYPE_4__ speakup_info ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spk_do_flush () ; 
 struct var_t* spk_get_var (int /*<<< orphan*/ ) ; 
 scalar_t__ spk_no_intr ; 
 int spk_parked ; 
 int spk_shut_up ; 
 int /*<<< orphan*/  synth ; 

__attribute__((used)) static void do_handle_cursor(struct vc_data *vc, u_char value, char up_flag)
{
	unsigned long flags;
	struct var_t *cursor_timeout;

	spin_lock_irqsave(&speakup_info.spinlock, flags);
	spk_parked &= 0xfe;
	if (!synth || up_flag || spk_shut_up || cursor_track == CT_Off) {
		spin_unlock_irqrestore(&speakup_info.spinlock, flags);
		return;
	}
	spk_shut_up &= 0xfe;
	if (spk_no_intr)
		spk_do_flush();
/* the key press flushes if !no_inter but we want to flush on cursor
 * moves regardless of no_inter state
 */
	is_cursor = value + 1;
	old_cursor_pos = vc->vc_pos;
	old_cursor_x = vc->vc_x;
	old_cursor_y = vc->vc_y;
	speakup_console[vc->vc_num]->ht.cy = vc->vc_y;
	cursor_con = vc->vc_num;
	if (cursor_track == CT_Highlight)
		reset_highlight_buffers(vc);
	cursor_timeout = spk_get_var(CURSOR_TIME);
	mod_timer(&cursor_timer,
		  jiffies + msecs_to_jiffies(cursor_timeout->u.n.value));
	spin_unlock_irqrestore(&speakup_info.spinlock, flags);
}