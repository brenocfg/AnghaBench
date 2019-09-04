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
struct serio {int dummy; } ;
struct TYPE_2__ {struct serio* serio; } ;

/* Variables and functions */
 size_t I8042_AUX_PORT_NO ; 
 int /*<<< orphan*/  I8042_CMD_CTL_WCTR ; 
 int I8042_CTR_AUXDIS ; 
 int I8042_CTR_AUXINT ; 
 int I8042_CTR_KBDDIS ; 
 int I8042_CTR_KBDINT ; 
 scalar_t__ i8042_command (int*,int /*<<< orphan*/ ) ; 
 int i8042_ctr ; 
 int /*<<< orphan*/  i8042_interrupt (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* i8042_ports ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  pr_warn (char*,char const*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void i8042_port_close(struct serio *serio)
{
	int irq_bit;
	int disable_bit;
	const char *port_name;

	if (serio == i8042_ports[I8042_AUX_PORT_NO].serio) {
		irq_bit = I8042_CTR_AUXINT;
		disable_bit = I8042_CTR_AUXDIS;
		port_name = "AUX";
	} else {
		irq_bit = I8042_CTR_KBDINT;
		disable_bit = I8042_CTR_KBDDIS;
		port_name = "KBD";
	}

	i8042_ctr &= ~irq_bit;
	if (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR))
		pr_warn("Can't write CTR while closing %s port\n", port_name);

	udelay(50);

	i8042_ctr &= ~disable_bit;
	i8042_ctr |= irq_bit;
	if (i8042_command(&i8042_ctr, I8042_CMD_CTL_WCTR))
		pr_err("Can't reactivate %s port\n", port_name);

	/*
	 * See if there is any data appeared while we were messing with
	 * port state.
	 */
	i8042_interrupt(0, NULL);
}