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
struct net_device {int dummy; } ;
struct hns3_nic_priv {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  HNS3_NIC_STATE_RESETTING ; 
 struct hns3_nic_priv* netdev_priv (struct net_device*) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool hns3_nic_resetting(struct net_device *netdev)
{
	struct hns3_nic_priv *priv = netdev_priv(netdev);

	return test_bit(HNS3_NIC_STATE_RESETTING, &priv->state);
}