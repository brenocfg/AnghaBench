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
struct altera_jtag {int irstop_state; } ;
typedef  enum altera_jtag_state { ____Placeholder_altera_jtag_state } altera_jtag_state ;

/* Variables and functions */

int altera_set_irstop(struct altera_jtag *js, enum altera_jtag_state state)
{
	js->irstop_state = state;

	return 0;
}