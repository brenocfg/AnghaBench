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
typedef  enum mlxsw_afa_virfwd_fid_cmd { ____Placeholder_mlxsw_afa_virfwd_fid_cmd } mlxsw_afa_virfwd_fid_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_virfwd_fid_cmd_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_afa_virfwd_fid_set (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_afa_virfwd_pack(char *payload,
					 enum mlxsw_afa_virfwd_fid_cmd fid_cmd,
					 u16 fid)
{
	mlxsw_afa_virfwd_fid_cmd_set(payload, fid_cmd);
	mlxsw_afa_virfwd_fid_set(payload, fid);
}