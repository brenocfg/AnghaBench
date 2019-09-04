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
struct ksz_hw {scalar_t__ io; } ;

/* Variables and functions */
 scalar_t__ KS8842_PORT_IN_RATE_OFFSET ; 
 int /*<<< orphan*/  PORT_CTRL_ADDR (int,scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sw_dis_prio_rate(struct ksz_hw *hw, int port)
{
	u32 addr;

	PORT_CTRL_ADDR(port, addr);
	addr += KS8842_PORT_IN_RATE_OFFSET;
	writel(0, hw->io + addr);
}