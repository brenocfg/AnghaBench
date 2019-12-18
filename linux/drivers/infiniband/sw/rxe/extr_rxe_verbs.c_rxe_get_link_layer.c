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
struct rxe_dev {int dummy; } ;
struct ib_device {int dummy; } ;
typedef  enum rdma_link_layer { ____Placeholder_rdma_link_layer } rdma_link_layer ;

/* Variables and functions */
 int rxe_link_layer (struct rxe_dev*,int /*<<< orphan*/ ) ; 
 struct rxe_dev* to_rdev (struct ib_device*) ; 

__attribute__((used)) static enum rdma_link_layer rxe_get_link_layer(struct ib_device *dev,
					       u8 port_num)
{
	struct rxe_dev *rxe = to_rdev(dev);

	return rxe_link_layer(rxe, port_num);
}