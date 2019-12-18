#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc_data {int /*<<< orphan*/  vc_num; } ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
struct TYPE_4__ {TYPE_1__ n; } ;
struct var_t {TYPE_2__ u; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURSOR_TIME ; 
 int /*<<< orphan*/  cursor_con ; 
 int /*<<< orphan*/  cursor_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int read_all_key ; 
 struct var_t* spk_get_var (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void start_read_all_timer(struct vc_data *vc, int command)
{
	struct var_t *cursor_timeout;

	cursor_con = vc->vc_num;
	read_all_key = command;
	cursor_timeout = spk_get_var(CURSOR_TIME);
	mod_timer(&cursor_timer,
		  jiffies + msecs_to_jiffies(cursor_timeout->u.n.value));
}