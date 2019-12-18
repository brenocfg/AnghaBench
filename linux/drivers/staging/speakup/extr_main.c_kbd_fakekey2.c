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
 int /*<<< orphan*/  cursor_timer ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  speakup_fake_down_arrow () ; 
 int /*<<< orphan*/  start_read_all_timer (struct vc_data*,int) ; 

__attribute__((used)) static void kbd_fakekey2(struct vc_data *vc, int command)
{
	del_timer(&cursor_timer);
	speakup_fake_down_arrow();
	start_read_all_timer(vc, command);
}