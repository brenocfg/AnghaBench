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
typedef  int /*<<< orphan*/  u8 ;
struct xps2data {scalar_t__ base_address; int /*<<< orphan*/  irq; int /*<<< orphan*/  dev; } ;
struct serio {struct xps2data* port_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  XPS2_GIER_GIE_MASK ; 
 scalar_t__ XPS2_GIER_OFFSET ; 
 scalar_t__ XPS2_IPIER_OFFSET ; 
 int /*<<< orphan*/  XPS2_IPIXR_RX_ALL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xps2data*) ; 
 int /*<<< orphan*/  xps2_interrupt ; 
 int /*<<< orphan*/  xps2_recv (struct xps2data*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sxps2_open(struct serio *pserio)
{
	struct xps2data *drvdata = pserio->port_data;
	int error;
	u8 c;

	error = request_irq(drvdata->irq, &xps2_interrupt, 0,
				DRIVER_NAME, drvdata);
	if (error) {
		dev_err(drvdata->dev,
			"Couldn't allocate interrupt %d\n", drvdata->irq);
		return error;
	}

	/* start reception by enabling the interrupts */
	out_be32(drvdata->base_address + XPS2_GIER_OFFSET, XPS2_GIER_GIE_MASK);
	out_be32(drvdata->base_address + XPS2_IPIER_OFFSET, XPS2_IPIXR_RX_ALL);
	(void)xps2_recv(drvdata, &c);

	return 0;		/* success */
}