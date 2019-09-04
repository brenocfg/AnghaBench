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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct rxe_dev {TYPE_1__ ib_dev; } ;
struct net_device {int dummy; } ;
struct kernel_param {int dummy; } ;
typedef  int /*<<< orphan*/  intf ;

/* Variables and functions */
 int EINVAL ; 
 struct net_device* dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 scalar_t__ net_to_rxe (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,char*) ; 
 struct rxe_dev* rxe_net_add (struct net_device*) ; 
 int /*<<< orphan*/  rxe_set_port_state (struct net_device*) ; 
 int sanitize_arg (char const*,char*,int) ; 

__attribute__((used)) static int rxe_param_set_add(const char *val, const struct kernel_param *kp)
{
	int len;
	int err = 0;
	char intf[32];
	struct net_device *ndev = NULL;
	struct rxe_dev *rxe;

	len = sanitize_arg(val, intf, sizeof(intf));
	if (!len) {
		pr_err("add: invalid interface name\n");
		err = -EINVAL;
		goto err;
	}

	ndev = dev_get_by_name(&init_net, intf);
	if (!ndev) {
		pr_err("interface %s not found\n", intf);
		err = -EINVAL;
		goto err;
	}

	if (net_to_rxe(ndev)) {
		pr_err("already configured on %s\n", intf);
		err = -EINVAL;
		goto err;
	}

	rxe = rxe_net_add(ndev);
	if (!rxe) {
		pr_err("failed to add %s\n", intf);
		err = -EINVAL;
		goto err;
	}

	rxe_set_port_state(ndev);
	pr_info("added %s to %s\n", rxe->ib_dev.name, intf);
err:
	if (ndev)
		dev_put(ndev);
	return err;
}