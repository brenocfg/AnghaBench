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

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_ptar_tcam_region_info_memcpy_from (char*,char*) ; 

__attribute__((used)) static inline void mlxsw_reg_ptar_unpack(char *payload, char *tcam_region_info)
{
	mlxsw_reg_ptar_tcam_region_info_memcpy_from(payload, tcam_region_info);
}