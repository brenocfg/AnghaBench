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
struct team_option {int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;
struct team {int dummy; } ;

/* Variables and functions */
 struct team_option* __team_find_option (struct team*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __team_option_inst_del_option (struct team*,struct team_option*) ; 
 int /*<<< orphan*/  kfree (struct team_option*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __team_options_unregister(struct team *team,
				      const struct team_option *option,
				      size_t option_count)
{
	int i;

	for (i = 0; i < option_count; i++, option++) {
		struct team_option *del_opt;

		del_opt = __team_find_option(team, option->name);
		if (del_opt) {
			__team_option_inst_del_option(team, del_opt);
			list_del(&del_opt->list);
			kfree(del_opt);
		}
	}
}