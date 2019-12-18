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
struct rp2_uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rp2_rmw (struct rp2_uart_port*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rp2_rmw_set(struct rp2_uart_port *up, int reg, u32 val)
{
	rp2_rmw(up, reg, 0, val);
}