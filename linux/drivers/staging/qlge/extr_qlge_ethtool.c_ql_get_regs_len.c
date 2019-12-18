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
struct ql_reg_dump {int dummy; } ;
struct ql_mpi_coredump {int dummy; } ;
struct ql_adapter {int /*<<< orphan*/  flags; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QL_FRC_COREDUMP ; 
 struct ql_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ql_get_regs_len(struct net_device *ndev)
{
	struct ql_adapter *qdev = netdev_priv(ndev);

	if (!test_bit(QL_FRC_COREDUMP, &qdev->flags))
		return sizeof(struct ql_mpi_coredump);
	else
		return sizeof(struct ql_reg_dump);
}