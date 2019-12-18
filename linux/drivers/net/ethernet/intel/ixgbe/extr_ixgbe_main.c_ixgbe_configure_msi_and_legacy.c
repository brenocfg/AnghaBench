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
struct ixgbe_q_vector {int dummy; } ;
struct ixgbe_adapter {struct ixgbe_q_vector** q_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  e_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  ixgbe_set_ivar (struct ixgbe_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_write_eitr (struct ixgbe_q_vector*) ; 

__attribute__((used)) static void ixgbe_configure_msi_and_legacy(struct ixgbe_adapter *adapter)
{
	struct ixgbe_q_vector *q_vector = adapter->q_vector[0];

	ixgbe_write_eitr(q_vector);

	ixgbe_set_ivar(adapter, 0, 0, 0);
	ixgbe_set_ivar(adapter, 1, 0, 0);

	e_info(hw, "Legacy interrupt IVAR setup done\n");
}