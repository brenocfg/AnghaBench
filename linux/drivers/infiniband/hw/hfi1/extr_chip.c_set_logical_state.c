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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCC_CFG_PORT_CONFIG ; 
 int DCC_CFG_PORT_CONFIG_LINK_STATE_SHIFT ; 
 int DCC_CFG_PORT_CONFIG_LINK_STATE_SMASK ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_logical_state(struct hfi1_devdata *dd, u32 chip_lstate)
{
	u64 reg;

	reg = read_csr(dd, DCC_CFG_PORT_CONFIG);
	/* clear current state, set new state */
	reg &= ~DCC_CFG_PORT_CONFIG_LINK_STATE_SMASK;
	reg |= (u64)chip_lstate << DCC_CFG_PORT_CONFIG_LINK_STATE_SHIFT;
	write_csr(dd, DCC_CFG_PORT_CONFIG, reg);
}