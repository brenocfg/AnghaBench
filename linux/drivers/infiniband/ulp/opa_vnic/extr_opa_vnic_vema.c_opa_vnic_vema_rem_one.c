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
struct opa_vnic_ctrl_port {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  c_info (char*) ; 
 int /*<<< orphan*/  kfree (struct opa_vnic_ctrl_port*) ; 
 int /*<<< orphan*/  opa_vnic_ctrl_config_dev (struct opa_vnic_ctrl_port*,int) ; 
 int /*<<< orphan*/  vema_unregister (struct opa_vnic_ctrl_port*) ; 

__attribute__((used)) static void opa_vnic_vema_rem_one(struct ib_device *device,
				  void *client_data)
{
	struct opa_vnic_ctrl_port *cport = client_data;

	if (!cport)
		return;

	c_info("removing VNIC client\n");
	opa_vnic_ctrl_config_dev(cport, false);
	vema_unregister(cport);
	kfree(cport);
}