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
struct socfpga_fpga_priv {scalar_t__ fpga_base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void socfpga_fpga_raw_writel(struct socfpga_fpga_priv *priv,
				    u32 reg_offset, u32 value)
{
	__raw_writel(value, priv->fpga_base_addr + reg_offset);
}