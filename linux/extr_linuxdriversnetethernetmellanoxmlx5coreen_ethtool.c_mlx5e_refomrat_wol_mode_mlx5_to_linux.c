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
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int MLX5_WOL_ARP ; 
 int MLX5_WOL_BROADCAST ; 
 int MLX5_WOL_MAGIC ; 
 int MLX5_WOL_MULTICAST ; 
 int MLX5_WOL_PHY_ACTIVITY ; 
 int MLX5_WOL_SECURED_MAGIC ; 
 int MLX5_WOL_UNICAST ; 
 int /*<<< orphan*/  WAKE_ARP ; 
 int /*<<< orphan*/  WAKE_BCAST ; 
 int /*<<< orphan*/  WAKE_MAGIC ; 
 int /*<<< orphan*/  WAKE_MAGICSECURE ; 
 int /*<<< orphan*/  WAKE_MCAST ; 
 int /*<<< orphan*/  WAKE_PHY ; 
 int /*<<< orphan*/  WAKE_UCAST ; 

__attribute__((used)) static __u32 mlx5e_refomrat_wol_mode_mlx5_to_linux(u8 mode)
{
	__u32 ret = 0;

	if (mode & MLX5_WOL_MAGIC)
		ret |= WAKE_MAGIC;

	if (mode & MLX5_WOL_SECURED_MAGIC)
		ret |= WAKE_MAGICSECURE;

	if (mode & MLX5_WOL_ARP)
		ret |= WAKE_ARP;

	if (mode & MLX5_WOL_BROADCAST)
		ret |= WAKE_BCAST;

	if (mode & MLX5_WOL_MULTICAST)
		ret |= WAKE_MCAST;

	if (mode & MLX5_WOL_UNICAST)
		ret |= WAKE_UCAST;

	if (mode & MLX5_WOL_PHY_ACTIVITY)
		ret |= WAKE_PHY;

	return ret;
}