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
struct rvin_group_route {int mask; scalar_t__ vin; int csi; unsigned char channel; } ;
struct rvin_dev {scalar_t__ id; TYPE_1__* info; } ;
typedef  enum rvin_csi_id { ____Placeholder_rvin_csi_id } rvin_csi_id ;
struct TYPE_2__ {struct rvin_group_route* routes; } ;

/* Variables and functions */
 int /*<<< orphan*/  vin_dbg (struct rvin_dev*,char*,scalar_t__,int,unsigned char) ; 

__attribute__((used)) static unsigned int rvin_group_get_mask(struct rvin_dev *vin,
					enum rvin_csi_id csi_id,
					unsigned char channel)
{
	const struct rvin_group_route *route;
	unsigned int mask = 0;

	for (route = vin->info->routes; route->mask; route++) {
		if (route->vin == vin->id &&
		    route->csi == csi_id &&
		    route->channel == channel) {
			vin_dbg(vin,
				"Adding route: vin: %d csi: %d channel: %d\n",
				route->vin, route->csi, route->channel);
			mask |= route->mask;
		}
	}

	return mask;
}