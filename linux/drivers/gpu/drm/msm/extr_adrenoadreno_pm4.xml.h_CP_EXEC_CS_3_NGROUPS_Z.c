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
typedef  int uint32_t ;

/* Variables and functions */
 int CP_EXEC_CS_3_NGROUPS_Z__MASK ; 
 int CP_EXEC_CS_3_NGROUPS_Z__SHIFT ; 

__attribute__((used)) static inline uint32_t CP_EXEC_CS_3_NGROUPS_Z(uint32_t val)
{
	return ((val) << CP_EXEC_CS_3_NGROUPS_Z__SHIFT) & CP_EXEC_CS_3_NGROUPS_Z__MASK;
}