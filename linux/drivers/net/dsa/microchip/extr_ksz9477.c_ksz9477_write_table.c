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
typedef  int /*<<< orphan*/  u32 ;
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SW_ALU_VAL_A ; 
 int /*<<< orphan*/  REG_SW_ALU_VAL_B ; 
 int /*<<< orphan*/  REG_SW_ALU_VAL_C ; 
 int /*<<< orphan*/  REG_SW_ALU_VAL_D ; 
 int /*<<< orphan*/  ksz_write32 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz9477_write_table(struct ksz_device *dev, u32 *table)
{
	ksz_write32(dev, REG_SW_ALU_VAL_A, table[0]);
	ksz_write32(dev, REG_SW_ALU_VAL_B, table[1]);
	ksz_write32(dev, REG_SW_ALU_VAL_C, table[2]);
	ksz_write32(dev, REG_SW_ALU_VAL_D, table[3]);
}