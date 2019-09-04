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
struct xps2data {int /*<<< orphan*/  irq; scalar_t__ base_address; } ;
struct serio {struct xps2data* port_data; } ;

/* Variables and functions */
 scalar_t__ XPS2_GIER_OFFSET ; 
 scalar_t__ XPS2_IPIER_OFFSET ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct xps2data*) ; 
 int /*<<< orphan*/  out_be32 (scalar_t__,int) ; 

__attribute__((used)) static void sxps2_close(struct serio *pserio)
{
	struct xps2data *drvdata = pserio->port_data;

	/* Disable the PS2 interrupts */
	out_be32(drvdata->base_address + XPS2_GIER_OFFSET, 0x00);
	out_be32(drvdata->base_address + XPS2_IPIER_OFFSET, 0x00);
	free_irq(drvdata->irq, drvdata);
}