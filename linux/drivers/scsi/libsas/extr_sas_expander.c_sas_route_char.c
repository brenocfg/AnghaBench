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
struct ex_phy {int routing_attr; } ;
struct TYPE_2__ {int /*<<< orphan*/  t2t_supp; } ;
struct domain_device {TYPE_1__ ex_dev; } ;

/* Variables and functions */
#define  DIRECT_ROUTING 130 
#define  SUBTRACTIVE_ROUTING 129 
#define  TABLE_ROUTING 128 

__attribute__((used)) static char sas_route_char(struct domain_device *dev, struct ex_phy *phy)
{
	switch (phy->routing_attr) {
	case TABLE_ROUTING:
		if (dev->ex_dev.t2t_supp)
			return 'U';
		else
			return 'T';
	case DIRECT_ROUTING:
		return 'D';
	case SUBTRACTIVE_ROUTING:
		return 'S';
	default:
		return '?';
	}
}