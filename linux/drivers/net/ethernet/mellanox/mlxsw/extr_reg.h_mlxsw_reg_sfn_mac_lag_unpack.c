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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_sfn_mac_fid_get (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfn_mac_lag_lag_id_get (char*,int) ; 
 int /*<<< orphan*/  mlxsw_reg_sfn_rec_mac_memcpy_from (char*,int,char*) ; 

__attribute__((used)) static inline void mlxsw_reg_sfn_mac_lag_unpack(char *payload, int rec_index,
						char *mac, u16 *p_vid,
						u16 *p_lag_id)
{
	mlxsw_reg_sfn_rec_mac_memcpy_from(payload, rec_index, mac);
	*p_vid = mlxsw_reg_sfn_mac_fid_get(payload, rec_index);
	*p_lag_id = mlxsw_reg_sfn_mac_lag_lag_id_get(payload, rec_index);
}