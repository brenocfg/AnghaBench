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
struct smi_port {int _dmaInterruptCH0; int _dmaInterruptCH1; struct smi_dev* dev; } ;
struct smi_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSI_INT_ENA_CLR ; 
 int /*<<< orphan*/  smi_write (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void smi_port_disableInterrupt(struct smi_port *port)
{
	struct smi_dev *dev = port->dev;

	smi_write(MSI_INT_ENA_CLR,
		(port->_dmaInterruptCH0 | port->_dmaInterruptCH1));
}