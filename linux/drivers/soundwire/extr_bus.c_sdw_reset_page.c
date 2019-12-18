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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int err_threshold; } ;
struct sdw_bus {TYPE_2__* ops; TYPE_1__ prop; } ;
typedef  enum sdw_command_response { ____Placeholder_sdw_command_response } sdw_command_response ;
struct TYPE_4__ {int (* reset_page_addr ) (struct sdw_bus*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ENODATA ; 
 int find_response_code (int) ; 
 int stub1 (struct sdw_bus*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sdw_reset_page(struct sdw_bus *bus, u16 dev_num)
{
	int retry = bus->prop.err_threshold;
	enum sdw_command_response resp;
	int ret = 0, i;

	for (i = 0; i <= retry; i++) {
		resp = bus->ops->reset_page_addr(bus, dev_num);
		ret = find_response_code(resp);
		/* if cmd is ok or ignored return */
		if (ret == 0 || ret == -ENODATA)
			return ret;
	}

	return ret;
}