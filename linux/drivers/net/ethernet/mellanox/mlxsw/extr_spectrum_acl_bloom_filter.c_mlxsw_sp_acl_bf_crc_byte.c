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
typedef  int u8 ;
typedef  int u16 ;

/* Variables and functions */
 int* mlxsw_sp_acl_bf_crc_tab ; 

__attribute__((used)) static u16 mlxsw_sp_acl_bf_crc_byte(u16 crc, u8 c)
{
	return (crc << 8) ^ mlxsw_sp_acl_bf_crc_tab[(crc >> 8) ^ c];
}