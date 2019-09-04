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
struct zynq_fpga_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MASK_OFFSET ; 
 int /*<<< orphan*/  zynq_fpga_write (struct zynq_fpga_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void zynq_fpga_set_irq(struct zynq_fpga_priv *priv, u32 enable)
{
	zynq_fpga_write(priv, INT_MASK_OFFSET, ~enable);
}