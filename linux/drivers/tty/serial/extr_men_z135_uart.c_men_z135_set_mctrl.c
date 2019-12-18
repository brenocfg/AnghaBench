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
struct uart_port {scalar_t__ membase; } ;

/* Variables and functions */
 scalar_t__ MEN_Z135_CONF_REG ; 
 int /*<<< orphan*/  MEN_Z135_MCR_DTR ; 
 int /*<<< orphan*/  MEN_Z135_MCR_LOOP ; 
 int /*<<< orphan*/  MEN_Z135_MCR_OUT1 ; 
 int /*<<< orphan*/  MEN_Z135_MCR_OUT2 ; 
 int /*<<< orphan*/  MEN_Z135_MCR_RTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_OUT1 ; 
 unsigned int TIOCM_OUT2 ; 
 unsigned int TIOCM_RTS ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void men_z135_set_mctrl(struct uart_port *port, unsigned int mctrl)
{
	u32 old;
	u32 conf_reg;

	conf_reg = old = ioread32(port->membase + MEN_Z135_CONF_REG);
	if (mctrl & TIOCM_RTS)
		conf_reg |= MEN_Z135_MCR_RTS;
	else
		conf_reg &= ~MEN_Z135_MCR_RTS;

	if (mctrl & TIOCM_DTR)
		conf_reg |= MEN_Z135_MCR_DTR;
	else
		conf_reg &= ~MEN_Z135_MCR_DTR;

	if (mctrl & TIOCM_OUT1)
		conf_reg |= MEN_Z135_MCR_OUT1;
	else
		conf_reg &= ~MEN_Z135_MCR_OUT1;

	if (mctrl & TIOCM_OUT2)
		conf_reg |= MEN_Z135_MCR_OUT2;
	else
		conf_reg &= ~MEN_Z135_MCR_OUT2;

	if (mctrl & TIOCM_LOOP)
		conf_reg |= MEN_Z135_MCR_LOOP;
	else
		conf_reg &= ~MEN_Z135_MCR_LOOP;

	if (conf_reg != old)
		iowrite32(conf_reg, port->membase + MEN_Z135_CONF_REG);
}