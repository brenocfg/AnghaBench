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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 scalar_t__ RT_TABLE_DEFAULT ; 
 scalar_t__ RT_TABLE_LOCAL ; 
 scalar_t__ RT_TABLE_MAIN ; 

__attribute__((used)) static u32 mlxsw_sp_fix_tb_id(u32 tb_id)
{
	/* For our purpose, squash main, default and local tables into one */
	if (tb_id == RT_TABLE_LOCAL || tb_id == RT_TABLE_DEFAULT)
		tb_id = RT_TABLE_MAIN;
	return tb_id;
}