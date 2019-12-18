#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union sab82532_async_regs {int dummy; } sab82532_async_regs ;
struct TYPE_2__ {int /*<<< orphan*/  membase; } ;
struct uart_sunsab_port {TYPE_1__ port; } ;
struct platform_device {int /*<<< orphan*/ * resource; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct uart_sunsab_port* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  sunsab_reg ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int sab_remove(struct platform_device *op)
{
	struct uart_sunsab_port *up = platform_get_drvdata(op);

	uart_remove_one_port(&sunsab_reg, &up[1].port);
	uart_remove_one_port(&sunsab_reg, &up[0].port);
	of_iounmap(&op->resource[0],
		   up[1].port.membase,
		   sizeof(union sab82532_async_regs));
	of_iounmap(&op->resource[0],
		   up[0].port.membase,
		   sizeof(union sab82532_async_regs));

	return 0;
}