#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct max310x_port {int /*<<< orphan*/  clk; TYPE_2__* p; TYPE_1__* devtype; } ;
struct device {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  line; } ;
struct TYPE_6__ {TYPE_3__ port; int /*<<< orphan*/  rs_work; int /*<<< orphan*/  md_work; int /*<<< orphan*/  tx_work; } ;
struct TYPE_5__ {int nr; int /*<<< orphan*/  (* power ) (TYPE_3__*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 struct max310x_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  max310x_lines ; 
 int /*<<< orphan*/  max310x_uart ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static int max310x_remove(struct device *dev)
{
	struct max310x_port *s = dev_get_drvdata(dev);
	int i;

	for (i = 0; i < s->devtype->nr; i++) {
		cancel_work_sync(&s->p[i].tx_work);
		cancel_work_sync(&s->p[i].md_work);
		cancel_work_sync(&s->p[i].rs_work);
		uart_remove_one_port(&max310x_uart, &s->p[i].port);
		clear_bit(s->p[i].port.line, max310x_lines);
		s->devtype->power(&s->p[i].port, 0);
	}

	clk_disable_unprepare(s->clk);

	return 0;
}