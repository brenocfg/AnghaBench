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
struct team_option {int /*<<< orphan*/  per_port; } ;
struct team {int dummy; } ;

/* Variables and functions */
 int __team_option_inst_add (struct team*,struct team_option*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __team_option_inst_del_option (struct team*,struct team_option*) ; 

__attribute__((used)) static int __team_option_inst_add_option(struct team *team,
					 struct team_option *option)
{
	int err;

	if (!option->per_port) {
		err = __team_option_inst_add(team, option, NULL);
		if (err)
			goto inst_del_option;
	}
	return 0;

inst_del_option:
	__team_option_inst_del_option(team, option);
	return err;
}