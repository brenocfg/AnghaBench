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
struct sdw_msg {int /*<<< orphan*/  len; } ;
struct sdw_defer {int /*<<< orphan*/  complete; int /*<<< orphan*/  length; struct sdw_msg* msg; } ;
struct TYPE_4__ {int err_threshold; } ;
struct sdw_bus {TYPE_1__* ops; TYPE_2__ prop; } ;
typedef  enum sdw_command_response { ____Placeholder_sdw_command_response } sdw_command_response ;
struct TYPE_3__ {int (* xfer_msg_defer ) (struct sdw_bus*,struct sdw_msg*,struct sdw_defer*) ;} ;

/* Variables and functions */
 int ENODATA ; 
 int find_response_code (int) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int stub1 (struct sdw_bus*,struct sdw_msg*,struct sdw_defer*) ; 

__attribute__((used)) static inline int do_transfer_defer(struct sdw_bus *bus,
				    struct sdw_msg *msg,
				    struct sdw_defer *defer)
{
	int retry = bus->prop.err_threshold;
	enum sdw_command_response resp;
	int ret = 0, i;

	defer->msg = msg;
	defer->length = msg->len;
	init_completion(&defer->complete);

	for (i = 0; i <= retry; i++) {
		resp = bus->ops->xfer_msg_defer(bus, msg, defer);
		ret = find_response_code(resp);
		/* if cmd is ok or ignored return */
		if (ret == 0 || ret == -ENODATA)
			return ret;
	}

	return ret;
}