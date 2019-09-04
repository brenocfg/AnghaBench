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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ fw_cfg_is_mmio ; 
 int /*<<< orphan*/  fw_cfg_reg_ctrl ; 
 int /*<<< orphan*/  iowrite16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite16be (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fw_cfg_sel_endianness(u16 key)
{
	if (fw_cfg_is_mmio)
		iowrite16be(key, fw_cfg_reg_ctrl);
	else
		iowrite16(key, fw_cfg_reg_ctrl);
}