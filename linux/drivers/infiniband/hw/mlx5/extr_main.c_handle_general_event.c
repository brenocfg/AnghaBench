#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_6__ {int /*<<< orphan*/  delay_drop_work; } ;
struct mlx5_ib_dev {TYPE_3__ delay_drop; int /*<<< orphan*/  ib_dev; } ;
struct TYPE_4__ {int port; } ;
struct TYPE_5__ {TYPE_1__ port; } ;
struct mlx5_eqe {int sub_type; TYPE_2__ data; } ;
struct ib_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_LINK_LAYER_ETHERNET ; 
#define  MLX5_GENERAL_SUBTYPE_DELAY_DROP_TIMEOUT 128 
 int /*<<< orphan*/  mlx5_ib_port_link_layer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_general_event(struct mlx5_ib_dev *ibdev, struct mlx5_eqe *eqe,
				 struct ib_event *ibev)
{
	u8 port = (eqe->data.port.port >> 4) & 0xf;

	switch (eqe->sub_type) {
	case MLX5_GENERAL_SUBTYPE_DELAY_DROP_TIMEOUT:
		if (mlx5_ib_port_link_layer(&ibdev->ib_dev, port) ==
					    IB_LINK_LAYER_ETHERNET)
			schedule_work(&ibdev->delay_drop.delay_drop_work);
		break;
	default: /* do nothing */
		return;
	}
}