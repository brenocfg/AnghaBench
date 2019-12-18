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
struct sifive_serial_port {int ier; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIFIVE_SERIAL_IE_OFFS ; 
 int SIFIVE_SERIAL_IE_RXWM_MASK ; 
 int /*<<< orphan*/  __ssp_writel (int,int /*<<< orphan*/ ,struct sifive_serial_port*) ; 

__attribute__((used)) static void __ssp_enable_rxwm(struct sifive_serial_port *ssp)
{
	if (ssp->ier & SIFIVE_SERIAL_IE_RXWM_MASK)
		return;

	ssp->ier |= SIFIVE_SERIAL_IE_RXWM_MASK;
	__ssp_writel(ssp->ier, SIFIVE_SERIAL_IE_OFFS, ssp);
}