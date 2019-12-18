#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct net_device {int dummy; } ;
struct ethtool_test {int flags; } ;
struct ef4_self_tests {int dummy; } ;
struct ef4_nic {scalar_t__ state; TYPE_1__* net_dev; } ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ETH_TEST_FL_FAILED ; 
 int ETH_TEST_FL_OFFLINE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int IFF_UP ; 
 scalar_t__ STATE_READY ; 
 int /*<<< orphan*/  dev_close (TYPE_1__*) ; 
 int dev_open (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  ef4_ethtool_fill_self_tests (struct ef4_nic*,struct ef4_self_tests*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ef4_selftest (struct ef4_nic*,struct ef4_self_tests*,int) ; 
 int /*<<< orphan*/  kfree (struct ef4_self_tests*) ; 
 struct ef4_self_tests* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct ef4_nic* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  netif_info (struct ef4_nic*,int /*<<< orphan*/ ,TYPE_1__*,char*,char*,...) ; 

__attribute__((used)) static void ef4_ethtool_self_test(struct net_device *net_dev,
				  struct ethtool_test *test, u64 *data)
{
	struct ef4_nic *efx = netdev_priv(net_dev);
	struct ef4_self_tests *ef4_tests;
	bool already_up;
	int rc = -ENOMEM;

	ef4_tests = kzalloc(sizeof(*ef4_tests), GFP_KERNEL);
	if (!ef4_tests)
		goto fail;

	if (efx->state != STATE_READY) {
		rc = -EBUSY;
		goto out;
	}

	netif_info(efx, drv, efx->net_dev, "starting %sline testing\n",
		   (test->flags & ETH_TEST_FL_OFFLINE) ? "off" : "on");

	/* We need rx buffers and interrupts. */
	already_up = (efx->net_dev->flags & IFF_UP);
	if (!already_up) {
		rc = dev_open(efx->net_dev, NULL);
		if (rc) {
			netif_err(efx, drv, efx->net_dev,
				  "failed opening device.\n");
			goto out;
		}
	}

	rc = ef4_selftest(efx, ef4_tests, test->flags);

	if (!already_up)
		dev_close(efx->net_dev);

	netif_info(efx, drv, efx->net_dev, "%s %sline self-tests\n",
		   rc == 0 ? "passed" : "failed",
		   (test->flags & ETH_TEST_FL_OFFLINE) ? "off" : "on");

out:
	ef4_ethtool_fill_self_tests(efx, ef4_tests, NULL, data);
	kfree(ef4_tests);
fail:
	if (rc)
		test->flags |= ETH_TEST_FL_FAILED;
}