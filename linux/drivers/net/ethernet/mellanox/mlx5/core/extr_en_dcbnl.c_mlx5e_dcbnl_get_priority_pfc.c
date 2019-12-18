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
typedef  int u8 ;
struct net_device {int dummy; } ;
struct ieee_pfc {int pfc_en; } ;

/* Variables and functions */
 int mlx5e_dcbnl_ieee_getpfc (struct net_device*,struct ieee_pfc*) ; 

__attribute__((used)) static int
mlx5e_dcbnl_get_priority_pfc(struct net_device *netdev,
			     int priority, u8 *setting)
{
	struct ieee_pfc pfc;
	int err;

	err = mlx5e_dcbnl_ieee_getpfc(netdev, &pfc);

	if (err)
		*setting = 0;
	else
		*setting = (pfc.pfc_en >> priority) & 0x01;

	return err;
}