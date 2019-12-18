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
struct rxe_dev {int /*<<< orphan*/  ib_dev; } ;
struct net_device {int dummy; } ;
struct kernel_param {int dummy; } ;
typedef  int /*<<< orphan*/  intf ;

/* Variables and functions */
 int EINVAL ; 
 struct net_device* dev_get_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  ib_device_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 struct rxe_dev* rxe_get_dev_from_net (struct net_device*) ; 
 int rxe_net_add (char*,struct net_device*) ; 
 int sanitize_arg (char const*,char*,int) ; 

__attribute__((used)) static int rxe_param_set_add(const char *val, const struct kernel_param *kp)
{
	int len;
	int err = 0;
	char intf[32];
	struct net_device *ndev;
	struct rxe_dev *exists;

	len = sanitize_arg(val, intf, sizeof(intf));
	if (!len) {
		pr_err("add: invalid interface name\n");
		return -EINVAL;
	}

	ndev = dev_get_by_name(&init_net, intf);
	if (!ndev) {
		pr_err("interface %s not found\n", intf);
		return -EINVAL;
	}

	exists = rxe_get_dev_from_net(ndev);
	if (exists) {
		ib_device_put(&exists->ib_dev);
		pr_err("already configured on %s\n", intf);
		err = -EINVAL;
		goto err;
	}

	err = rxe_net_add("rxe%d", ndev);
	if (err) {
		pr_err("failed to add %s\n", intf);
		goto err;
	}

err:
	dev_put(ndev);
	return err;
}