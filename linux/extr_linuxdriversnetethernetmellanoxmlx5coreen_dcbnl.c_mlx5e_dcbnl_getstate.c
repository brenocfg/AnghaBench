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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_CEE_STATE_UP ; 

__attribute__((used)) static u8 mlx5e_dcbnl_getstate(struct net_device *netdev)
{
	return MLX5E_CEE_STATE_UP;
}