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
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_WOL_ARP ; 
 int /*<<< orphan*/  MLX5_WOL_BROADCAST ; 
 int /*<<< orphan*/  MLX5_WOL_MAGIC ; 
 int /*<<< orphan*/  MLX5_WOL_MULTICAST ; 
 int /*<<< orphan*/  MLX5_WOL_PHY_ACTIVITY ; 
 int /*<<< orphan*/  MLX5_WOL_SECURED_MAGIC ; 
 int /*<<< orphan*/  MLX5_WOL_UNICAST ; 
 int WAKE_ARP ; 
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int WAKE_MAGICSECURE ; 
 int WAKE_MCAST ; 
 int WAKE_PHY ; 
 int WAKE_UCAST ; 

__attribute__((used)) static u8 mlx5e_refomrat_wol_mode_linux_to_mlx5(__u32 mode)
{
	u8 ret = 0;

	if (mode & WAKE_MAGIC)
		ret |= MLX5_WOL_MAGIC;

	if (mode & WAKE_MAGICSECURE)
		ret |= MLX5_WOL_SECURED_MAGIC;

	if (mode & WAKE_ARP)
		ret |= MLX5_WOL_ARP;

	if (mode & WAKE_BCAST)
		ret |= MLX5_WOL_BROADCAST;

	if (mode & WAKE_MCAST)
		ret |= MLX5_WOL_MULTICAST;

	if (mode & WAKE_UCAST)
		ret |= MLX5_WOL_UNICAST;

	if (mode & WAKE_PHY)
		ret |= MLX5_WOL_PHY_ACTIVITY;

	return ret;
}