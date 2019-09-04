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
typedef  int /*<<< orphan*/  u8 ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ rdma_protocol_iwarp (struct ib_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_rw_force_mr ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool rdma_rw_can_use_mr(struct ib_device *dev, u8 port_num)
{
	if (rdma_protocol_iwarp(dev, port_num))
		return true;
	if (unlikely(rdma_rw_force_mr))
		return true;
	return false;
}