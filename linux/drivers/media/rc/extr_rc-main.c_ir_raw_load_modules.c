#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int type; int /*<<< orphan*/  name; int /*<<< orphan*/  module_name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int RC_PROTO_BIT_NONE ; 
 int RC_PROTO_BIT_OTHER ; 
 int RC_PROTO_BIT_UNKNOWN ; 
 int ir_raw_get_allowed_protocols () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* proto_names ; 
 int request_module (char*,int /*<<< orphan*/ ) ; 

void ir_raw_load_modules(u64 *protocols)
{
	u64 available;
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(proto_names); i++) {
		if (proto_names[i].type == RC_PROTO_BIT_NONE ||
		    proto_names[i].type & (RC_PROTO_BIT_OTHER |
					   RC_PROTO_BIT_UNKNOWN))
			continue;

		available = ir_raw_get_allowed_protocols();
		if (!(*protocols & proto_names[i].type & ~available))
			continue;

		if (!proto_names[i].module_name) {
			pr_err("Can't enable IR protocol %s\n",
			       proto_names[i].name);
			*protocols &= ~proto_names[i].type;
			continue;
		}

		ret = request_module("%s", proto_names[i].module_name);
		if (ret < 0) {
			pr_err("Couldn't load IR protocol module %s\n",
			       proto_names[i].module_name);
			*protocols &= ~proto_names[i].type;
			continue;
		}
		msleep(20);
		available = ir_raw_get_allowed_protocols();
		if (!(*protocols & proto_names[i].type & ~available))
			continue;

		pr_err("Loaded IR protocol module %s, but protocol %s still not available\n",
		       proto_names[i].module_name,
		       proto_names[i].name);
		*protocols &= ~proto_names[i].type;
	}
}