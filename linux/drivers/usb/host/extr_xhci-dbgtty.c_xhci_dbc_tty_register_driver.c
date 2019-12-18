#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct xhci_hcd {struct xhci_dbc* dbc; } ;
struct xhci_dbc {int /*<<< orphan*/  port; } ;
struct TYPE_9__ {int c_cflag; int c_ispeed; int c_ospeed; } ;
struct TYPE_10__ {char* driver_name; char* name; int /*<<< orphan*/ * driver_state; TYPE_1__ init_termios; int /*<<< orphan*/  subtype; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int B9600 ; 
 int CLOCAL ; 
 int CREAD ; 
 int CS8 ; 
 int HUPCL ; 
 scalar_t__ IS_ERR (TYPE_2__*) ; 
 int PTR_ERR (TYPE_2__*) ; 
 int /*<<< orphan*/  SERIAL_TYPE_NORMAL ; 
 int TTY_DRIVER_DYNAMIC_DEV ; 
 int TTY_DRIVER_REAL_RAW ; 
 int /*<<< orphan*/  TTY_DRIVER_TYPE_SERIAL ; 
 TYPE_2__* dbc_tty_driver ; 
 int /*<<< orphan*/  dbc_tty_ops ; 
 int /*<<< orphan*/  put_tty_driver (TYPE_2__*) ; 
 TYPE_2__* tty_alloc_driver (int,int) ; 
 int tty_register_driver (TYPE_2__*) ; 
 int /*<<< orphan*/  tty_set_operations (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_1__ tty_std_termios ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,int) ; 

int xhci_dbc_tty_register_driver(struct xhci_hcd *xhci)
{
	int			status;
	struct xhci_dbc		*dbc = xhci->dbc;

	dbc_tty_driver = tty_alloc_driver(1, TTY_DRIVER_REAL_RAW |
					  TTY_DRIVER_DYNAMIC_DEV);
	if (IS_ERR(dbc_tty_driver)) {
		status = PTR_ERR(dbc_tty_driver);
		dbc_tty_driver = NULL;
		return status;
	}

	dbc_tty_driver->driver_name = "dbc_serial";
	dbc_tty_driver->name = "ttyDBC";

	dbc_tty_driver->type = TTY_DRIVER_TYPE_SERIAL;
	dbc_tty_driver->subtype = SERIAL_TYPE_NORMAL;
	dbc_tty_driver->init_termios = tty_std_termios;
	dbc_tty_driver->init_termios.c_cflag =
			B9600 | CS8 | CREAD | HUPCL | CLOCAL;
	dbc_tty_driver->init_termios.c_ispeed = 9600;
	dbc_tty_driver->init_termios.c_ospeed = 9600;
	dbc_tty_driver->driver_state = &dbc->port;

	tty_set_operations(dbc_tty_driver, &dbc_tty_ops);

	status = tty_register_driver(dbc_tty_driver);
	if (status) {
		xhci_err(xhci,
			 "can't register dbc tty driver, err %d\n", status);
		put_tty_driver(dbc_tty_driver);
		dbc_tty_driver = NULL;
	}

	return status;
}