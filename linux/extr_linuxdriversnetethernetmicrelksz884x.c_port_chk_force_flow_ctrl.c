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
 int /*<<< orphan*/  PORT_FORCE_FLOW_CTRL ; 
 int port_chk (struct ksz_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int port_chk_force_flow_ctrl(struct ksz_hw *hw, int p)
{
	return port_chk(hw, p,
		KS8842_PORT_CTRL_2_OFFSET, PORT_FORCE_FLOW_CTRL);
}