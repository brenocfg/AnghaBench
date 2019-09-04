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
typedef  int u32 ;
struct alu_struct {int is_static; int is_src_filter; int is_dst_filter; int prio_age; int mstp; int is_override; int is_use_fid; int port_forward; int fid; int* mac; } ;

/* Variables and functions */
 int ALU_V_DST_FILTER ; 
 int ALU_V_FID_M ; 
 int ALU_V_FID_S ; 
 int ALU_V_MSTP_M ; 
 int ALU_V_OVERRIDE ; 
 int ALU_V_PORT_MAP ; 
 int ALU_V_PRIO_AGE_CNT_M ; 
 int ALU_V_PRIO_AGE_CNT_S ; 
 int ALU_V_SRC_FILTER ; 
 int ALU_V_STATIC_VALID ; 
 int ALU_V_USE_FID ; 

__attribute__((used)) static void convert_alu(struct alu_struct *alu, u32 *alu_table)
{
	alu->is_static = !!(alu_table[0] & ALU_V_STATIC_VALID);
	alu->is_src_filter = !!(alu_table[0] & ALU_V_SRC_FILTER);
	alu->is_dst_filter = !!(alu_table[0] & ALU_V_DST_FILTER);
	alu->prio_age = (alu_table[0] >> ALU_V_PRIO_AGE_CNT_S) &
			ALU_V_PRIO_AGE_CNT_M;
	alu->mstp = alu_table[0] & ALU_V_MSTP_M;

	alu->is_override = !!(alu_table[1] & ALU_V_OVERRIDE);
	alu->is_use_fid = !!(alu_table[1] & ALU_V_USE_FID);
	alu->port_forward = alu_table[1] & ALU_V_PORT_MAP;

	alu->fid = (alu_table[2] >> ALU_V_FID_S) & ALU_V_FID_M;

	alu->mac[0] = (alu_table[2] >> 8) & 0xFF;
	alu->mac[1] = alu_table[2] & 0xFF;
	alu->mac[2] = (alu_table[3] >> 24) & 0xFF;
	alu->mac[3] = (alu_table[3] >> 16) & 0xFF;
	alu->mac[4] = (alu_table[3] >> 8) & 0xFF;
	alu->mac[5] = alu_table[3] & 0xFF;
}