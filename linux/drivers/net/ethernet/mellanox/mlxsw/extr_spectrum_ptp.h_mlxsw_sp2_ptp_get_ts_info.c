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
struct mlxsw_sp {int dummy; } ;
struct ethtool_ts_info {int dummy; } ;

/* Variables and functions */
 int mlxsw_sp_ptp_get_ts_info_noptp (struct ethtool_ts_info*) ; 

__attribute__((used)) static inline int mlxsw_sp2_ptp_get_ts_info(struct mlxsw_sp *mlxsw_sp,
					    struct ethtool_ts_info *info)
{
	return mlxsw_sp_ptp_get_ts_info_noptp(info);
}