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
struct TYPE_3__ {struct core_component* comp; } ;
struct TYPE_4__ {struct core_component* comp; } ;
struct most_channel {int /*<<< orphan*/  cfg; int /*<<< orphan*/  channel_id; int /*<<< orphan*/  iface; TYPE_1__ pipe1; TYPE_2__ pipe0; } ;
struct core_component {int (* probe_channel ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ;} ;

/* Variables and functions */
 int ENOSPC ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static
inline int link_channel_to_component(struct most_channel *c,
				     struct core_component *comp,
				     char *name,
				     char *comp_param)
{
	int ret;
	struct core_component **comp_ptr;

	if (!c->pipe0.comp)
		comp_ptr = &c->pipe0.comp;
	else if (!c->pipe1.comp)
		comp_ptr = &c->pipe1.comp;
	else
		return -ENOSPC;

	*comp_ptr = comp;
	ret = comp->probe_channel(c->iface, c->channel_id, &c->cfg, name,
				  comp_param);
	if (ret) {
		*comp_ptr = NULL;
		return ret;
	}
	return 0;
}