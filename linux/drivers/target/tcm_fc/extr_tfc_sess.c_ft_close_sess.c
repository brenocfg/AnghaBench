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
struct ft_sess {int /*<<< orphan*/  se_sess; } ;

/* Variables and functions */
 int /*<<< orphan*/  ft_sess_put (struct ft_sess*) ; 
 int /*<<< orphan*/  target_sess_cmd_list_set_waiting (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_wait_for_sess_cmds (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ft_close_sess(struct ft_sess *sess)
{
	target_sess_cmd_list_set_waiting(sess->se_sess);
	target_wait_for_sess_cmds(sess->se_sess);
	ft_sess_put(sess);
}