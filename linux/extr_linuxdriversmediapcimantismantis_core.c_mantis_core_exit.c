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
struct mantis_pci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MANTIS_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ mantis_dma_exit (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_dma_stop (struct mantis_pci*) ; 
 scalar_t__ mantis_dvb_exit (struct mantis_pci*) ; 
 scalar_t__ mantis_i2c_exit (struct mantis_pci*) ; 
 int /*<<< orphan*/  mantis_uart_exit (struct mantis_pci*) ; 
 int /*<<< orphan*/  verbose ; 

int mantis_core_exit(struct mantis_pci *mantis)
{
	mantis_dma_stop(mantis);
	dprintk(verbose, MANTIS_ERROR, 1, "DMA engine stopping");

	mantis_uart_exit(mantis);
	dprintk(verbose, MANTIS_ERROR, 1, "UART exit failed");

	if (mantis_dma_exit(mantis) < 0)
		dprintk(verbose, MANTIS_ERROR, 1, "DMA exit failed");
	if (mantis_dvb_exit(mantis) < 0)
		dprintk(verbose, MANTIS_ERROR, 1, "DVB exit failed");
	if (mantis_i2c_exit(mantis) < 0)
		dprintk(verbose, MANTIS_ERROR, 1, "I2C adapter delete.. failed");

	return 0;
}