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
struct tb_port {int /*<<< orphan*/  sw; } ;

/* Variables and functions */
 int /*<<< orphan*/  TB_CFG_PORT ; 
 int /*<<< orphan*/  tb_port_read (struct tb_port*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ tb_switch_is_lr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tb_port_dummy_read(struct tb_port *port)
{
	/*
	 * When reading from next capability pointer location in port
	 * config space the read data is not cleared on LR. To avoid
	 * reading stale data on next read perform one dummy read after
	 * port capabilities are walked.
	 */
	if (tb_switch_is_lr(port->sw)) {
		u32 dummy;

		tb_port_read(port, &dummy, TB_CFG_PORT, 0, 1);
	}
}