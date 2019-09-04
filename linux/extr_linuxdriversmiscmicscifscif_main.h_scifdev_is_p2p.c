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
struct scif_dev {int dummy; } ;

/* Variables and functions */
 size_t SCIF_MGMT_NODE ; 
 struct scif_dev* scif_dev ; 
 scalar_t__ scif_is_mgmt_node () ; 
 int /*<<< orphan*/  scifdev_self (struct scif_dev*) ; 

__attribute__((used)) static inline bool scifdev_is_p2p(struct scif_dev *dev)
{
	if (scif_is_mgmt_node())
		return false;
	else
		return dev != &scif_dev[SCIF_MGMT_NODE] &&
			!scifdev_self(dev);
}