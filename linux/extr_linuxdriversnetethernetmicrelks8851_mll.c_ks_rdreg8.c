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
struct ks_net {int cmd_reg_cache; int /*<<< orphan*/  hw_addr; int /*<<< orphan*/  hw_addr_cmd; } ;

/* Variables and functions */
 int BE0 ; 
 int ioread16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 ks_rdreg8(struct ks_net *ks, int offset)
{
	u16 data;
	u8 shift_bit = offset & 0x03;
	u8 shift_data = (offset & 1) << 3;
	ks->cmd_reg_cache = (u16) offset | (u16)(BE0 << shift_bit);
	iowrite16(ks->cmd_reg_cache, ks->hw_addr_cmd);
	data  = ioread16(ks->hw_addr);
	return (u8)(data >> shift_data);
}