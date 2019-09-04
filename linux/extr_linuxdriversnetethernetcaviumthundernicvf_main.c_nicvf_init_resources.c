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
struct nicvf {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int nicvf_config_data_transfer (struct nicvf*,int) ; 
 int /*<<< orphan*/  nicvf_qset_config (struct nicvf*,int) ; 

__attribute__((used)) static int nicvf_init_resources(struct nicvf *nic)
{
	int err;

	/* Enable Qset */
	nicvf_qset_config(nic, true);

	/* Initialize queues and HW for data transfer */
	err = nicvf_config_data_transfer(nic, true);
	if (err) {
		netdev_err(nic->netdev,
			   "Failed to alloc/config VF's QSet resources\n");
		return err;
	}

	return 0;
}