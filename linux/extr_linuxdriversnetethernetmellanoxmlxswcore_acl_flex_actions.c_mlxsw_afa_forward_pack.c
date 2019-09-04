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
typedef  int /*<<< orphan*/  u32 ;
typedef  enum mlxsw_afa_forward_type { ____Placeholder_mlxsw_afa_forward_type } mlxsw_afa_forward_type ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_afa_forward_in_port_set (char*,int) ; 
 int /*<<< orphan*/  mlxsw_afa_forward_pbs_ptr_set (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_afa_forward_type_set (char*,int) ; 

__attribute__((used)) static inline void
mlxsw_afa_forward_pack(char *payload, enum mlxsw_afa_forward_type type,
		       u32 pbs_ptr, bool in_port)
{
	mlxsw_afa_forward_type_set(payload, type);
	mlxsw_afa_forward_pbs_ptr_set(payload, pbs_ptr);
	mlxsw_afa_forward_in_port_set(payload, in_port);
}