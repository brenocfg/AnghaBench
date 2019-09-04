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
struct ksz_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KS8842_PORT_CTRL_2_OFFSET ; 
 int /*<<< orphan*/  PORT_RX_ENABLE ; 
 int /*<<< orphan*/  port_cfg (struct ksz_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void port_cfg_rx(struct ksz_hw *hw, int p, int set)
{
	port_cfg(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_RX_ENABLE, set);
}