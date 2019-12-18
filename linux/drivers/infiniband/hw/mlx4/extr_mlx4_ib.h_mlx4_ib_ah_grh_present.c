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
struct TYPE_5__ {int g_slid; int /*<<< orphan*/  port_pd; } ;
struct TYPE_6__ {TYPE_2__ ib; } ;
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct mlx4_ib_ah {TYPE_3__ av; TYPE_1__ ibah; } ;

/* Variables and functions */
 scalar_t__ IB_LINK_LAYER_ETHERNET ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_port_get_link_layer (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline bool mlx4_ib_ah_grh_present(struct mlx4_ib_ah *ah)
{
	u8 port = be32_to_cpu(ah->av.ib.port_pd) >> 24 & 3;

	if (rdma_port_get_link_layer(ah->ibah.device, port) == IB_LINK_LAYER_ETHERNET)
		return true;

	return !!(ah->av.ib.g_slid & 0x80);
}