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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  mlxsw_reg_mfsl_tach_max_get (char*) ; 
 int /*<<< orphan*/  mlxsw_reg_mfsl_tach_min_get (char*) ; 

__attribute__((used)) static inline void mlxsw_reg_mfsl_unpack(char *payload, u8 tacho,
					 u16 *p_tach_min, u16 *p_tach_max)
{
	if (p_tach_min)
		*p_tach_min = mlxsw_reg_mfsl_tach_min_get(payload);

	if (p_tach_max)
		*p_tach_max = mlxsw_reg_mfsl_tach_max_get(payload);
}