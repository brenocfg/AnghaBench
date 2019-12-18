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
 int /*<<< orphan*/  mlxsw_reg_ptar_flexible_key_id_set (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void mlxsw_reg_ptar_key_id_pack(char *payload, int index,
					      u16 key_id)
{
	mlxsw_reg_ptar_flexible_key_id_set(payload, index, key_id);
}