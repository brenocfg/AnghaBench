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
typedef  enum fs_flow_table_type { ____Placeholder_fs_flow_table_type } fs_flow_table_type ;

/* Variables and functions */
 int FS_FT_NIC_RX ; 
 int FS_FT_NIC_TX ; 

__attribute__((used)) static enum fs_flow_table_type egress_to_fs_ft(bool egress)
{
	return egress ? FS_FT_NIC_TX : FS_FT_NIC_RX;
}