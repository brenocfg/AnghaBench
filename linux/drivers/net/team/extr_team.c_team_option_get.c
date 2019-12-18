#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct team_option_inst {TYPE_1__* option; } ;
struct team_gsetter_ctx {int dummy; } ;
struct team {int dummy; } ;
struct TYPE_2__ {int (* getter ) (struct team*,struct team_gsetter_ctx*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int stub1 (struct team*,struct team_gsetter_ctx*) ; 

__attribute__((used)) static int team_option_get(struct team *team,
			   struct team_option_inst *opt_inst,
			   struct team_gsetter_ctx *ctx)
{
	if (!opt_inst->option->getter)
		return -EOPNOTSUPP;
	return opt_inst->option->getter(team, ctx);
}