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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BS_B ; 
 int /*<<< orphan*/  BS_S ; 
 int /*<<< orphan*/  IR_B ; 
 int /*<<< orphan*/  IR_S ; 
 int /*<<< orphan*/  IR_U ; 
 int /*<<< orphan*/  hclge_tm_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 hclge_tm_get_shapping_para(u8 ir_b, u8 ir_u, u8 ir_s,
				      u8 bs_b, u8 bs_s)
{
	u32 shapping_para = 0;

	hclge_tm_set_field(shapping_para, IR_B, ir_b);
	hclge_tm_set_field(shapping_para, IR_U, ir_u);
	hclge_tm_set_field(shapping_para, IR_S, ir_s);
	hclge_tm_set_field(shapping_para, BS_B, bs_b);
	hclge_tm_set_field(shapping_para, BS_S, bs_s);

	return shapping_para;
}