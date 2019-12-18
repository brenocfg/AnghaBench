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
struct ieee_pfc {scalar_t__ pfc_en; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_CEE_STATE_DOWN ; 
 int /*<<< orphan*/  MLX5E_CEE_STATE_UP ; 
 scalar_t__ mlx5e_dcbnl_ieee_getpfc (struct net_device*,struct ieee_pfc*) ; 

__attribute__((used)) static u8 mlx5e_dcbnl_getpfcstate(struct net_device *netdev)
{
	struct ieee_pfc pfc;

	if (mlx5e_dcbnl_ieee_getpfc(netdev, &pfc))
		return MLX5E_CEE_STATE_DOWN;

	return pfc.pfc_en ? MLX5E_CEE_STATE_UP : MLX5E_CEE_STATE_DOWN;
}