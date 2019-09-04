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
struct grip_port {int buttons; scalar_t__ dirty; int /*<<< orphan*/  dev; int /*<<< orphan*/  yaxes; int /*<<< orphan*/  xaxes; } ;
struct grip_mp {struct grip_port** port; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/ * grip_btn_gp ; 
 int /*<<< orphan*/  input_report_abs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void report_slot(struct grip_mp *grip, int slot)
{
	struct grip_port *port = grip->port[slot];
	int i;

	/* Store button states with linux input driver */

	for (i = 0; i < 8; i++)
		input_report_key(port->dev, grip_btn_gp[i], (port->buttons >> i) & 1);

	/* Store axis states with linux driver */

	input_report_abs(port->dev, ABS_X, port->xaxes);
	input_report_abs(port->dev, ABS_Y, port->yaxes);

	/* Tell the receiver of the events to process them */

	input_sync(port->dev);

	port->dirty = 0;
}