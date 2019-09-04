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
struct qede_dev {int dummy; } ;
struct qede_arfs_tuple {int /*<<< orphan*/  ip_proto; } ;
struct ethtool_rx_flow_spec {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ qede_flow_spec_to_tuple_ipv4_common (struct qede_dev*,struct qede_arfs_tuple*,struct ethtool_rx_flow_spec*) ; 

__attribute__((used)) static int qede_flow_spec_to_tuple_tcpv4(struct qede_dev *edev,
					 struct qede_arfs_tuple *t,
					 struct ethtool_rx_flow_spec *fs)
{
	t->ip_proto = IPPROTO_TCP;

	if (qede_flow_spec_to_tuple_ipv4_common(edev, t, fs))
		return -EINVAL;

	return 0;
}