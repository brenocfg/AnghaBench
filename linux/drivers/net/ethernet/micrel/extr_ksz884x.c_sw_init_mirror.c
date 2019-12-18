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
 int TOTAL_PORT_NUM ; 
 int /*<<< orphan*/  port_cfg_mirror_rx (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_cfg_mirror_sniffer (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  port_cfg_mirror_tx (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_cfg_mirror_rx_tx (struct ksz_hw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sw_init_mirror(struct ksz_hw *hw)
{
	int port;

	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		port_cfg_mirror_sniffer(hw, port, 0);
		port_cfg_mirror_rx(hw, port, 0);
		port_cfg_mirror_tx(hw, port, 0);
	}
	sw_cfg_mirror_rx_tx(hw, 0);
}