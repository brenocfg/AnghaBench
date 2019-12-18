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
struct ib_device {unsigned int phys_port_cnt; } ;
struct cma_device {int dummy; } ;
struct cma_dev_port_group {unsigned int port_num; int /*<<< orphan*/  group; struct cma_dev_group* cma_dev_group; } ;
struct cma_dev_group {struct cma_dev_port_group* ports; int /*<<< orphan*/  ports_group; } ;
typedef  int /*<<< orphan*/  port_str ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ib_device* cma_get_ib_dev (struct cma_device*) ; 
 int /*<<< orphan*/  cma_port_group_type ; 
 int /*<<< orphan*/  config_group_init_type_name (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cma_dev_port_group* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct cma_dev_port_group*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static int make_cma_ports(struct cma_dev_group *cma_dev_group,
			  struct cma_device *cma_dev)
{
	struct ib_device *ibdev;
	unsigned int i;
	unsigned int ports_num;
	struct cma_dev_port_group *ports;
	int err;

	ibdev = cma_get_ib_dev(cma_dev);

	if (!ibdev)
		return -ENODEV;

	ports_num = ibdev->phys_port_cnt;
	ports = kcalloc(ports_num, sizeof(*cma_dev_group->ports),
			GFP_KERNEL);

	if (!ports) {
		err = -ENOMEM;
		goto free;
	}

	for (i = 0; i < ports_num; i++) {
		char port_str[10];

		ports[i].port_num = i + 1;
		snprintf(port_str, sizeof(port_str), "%u", i + 1);
		ports[i].cma_dev_group = cma_dev_group;
		config_group_init_type_name(&ports[i].group,
					    port_str,
					    &cma_port_group_type);
		configfs_add_default_group(&ports[i].group,
				&cma_dev_group->ports_group);

	}
	cma_dev_group->ports = ports;

	return 0;
free:
	kfree(ports);
	cma_dev_group->ports = NULL;
	return err;
}