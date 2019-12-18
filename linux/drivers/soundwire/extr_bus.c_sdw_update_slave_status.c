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
struct sdw_slave {TYPE_1__* ops; } ;
typedef  enum sdw_slave_status { ____Placeholder_sdw_slave_status } sdw_slave_status ;
struct TYPE_2__ {int (* update_status ) (struct sdw_slave*,int) ;} ;

/* Variables and functions */
 int stub1 (struct sdw_slave*,int) ; 

__attribute__((used)) static int sdw_update_slave_status(struct sdw_slave *slave,
				   enum sdw_slave_status status)
{
	if (slave->ops && slave->ops->update_status)
		return slave->ops->update_status(slave, status);

	return 0;
}