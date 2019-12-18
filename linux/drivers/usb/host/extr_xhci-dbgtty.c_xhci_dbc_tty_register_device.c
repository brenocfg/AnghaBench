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
struct xhci_hcd {struct xhci_dbc* dbc; } ;
struct dbc_port {int registered; int /*<<< orphan*/  write_fifo; int /*<<< orphan*/  write_pool; int /*<<< orphan*/  out; int /*<<< orphan*/  read_pool; int /*<<< orphan*/  in; int /*<<< orphan*/  port; } ;
struct xhci_dbc {struct dbc_port port; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBC_WRITE_BUF_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int /*<<< orphan*/  dbc_read_complete ; 
 int /*<<< orphan*/  dbc_tty_driver ; 
 int /*<<< orphan*/  dbc_write_complete ; 
 int kfifo_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfifo_free (int /*<<< orphan*/ *) ; 
 struct device* tty_port_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int xhci_dbc_alloc_requests (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_dbc_free_requests (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_dbc_tty_exit_port (struct dbc_port*) ; 
 int /*<<< orphan*/  xhci_dbc_tty_init_port (struct xhci_hcd*,struct dbc_port*) ; 
 int /*<<< orphan*/  xhci_err (struct xhci_hcd*,char*,int) ; 

int xhci_dbc_tty_register_device(struct xhci_hcd *xhci)
{
	int			ret;
	struct device		*tty_dev;
	struct xhci_dbc		*dbc = xhci->dbc;
	struct dbc_port		*port = &dbc->port;

	xhci_dbc_tty_init_port(xhci, port);
	tty_dev = tty_port_register_device(&port->port,
					   dbc_tty_driver, 0, NULL);
	if (IS_ERR(tty_dev)) {
		ret = PTR_ERR(tty_dev);
		goto register_fail;
	}

	ret = kfifo_alloc(&port->write_fifo, DBC_WRITE_BUF_SIZE, GFP_KERNEL);
	if (ret)
		goto buf_alloc_fail;

	ret = xhci_dbc_alloc_requests(port->in, &port->read_pool,
				      dbc_read_complete);
	if (ret)
		goto request_fail;

	ret = xhci_dbc_alloc_requests(port->out, &port->write_pool,
				      dbc_write_complete);
	if (ret)
		goto request_fail;

	port->registered = true;

	return 0;

request_fail:
	xhci_dbc_free_requests(port->in, &port->read_pool);
	xhci_dbc_free_requests(port->out, &port->write_pool);
	kfifo_free(&port->write_fifo);

buf_alloc_fail:
	tty_unregister_device(dbc_tty_driver, 0);

register_fail:
	xhci_dbc_tty_exit_port(port);

	xhci_err(xhci, "can't register tty port, err %d\n", ret);

	return ret;
}