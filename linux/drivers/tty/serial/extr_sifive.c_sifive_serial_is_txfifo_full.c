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
struct sifive_serial_port {int dummy; } ;

/* Variables and functions */
 int SIFIVE_SERIAL_TXDATA_FULL_MASK ; 
 int /*<<< orphan*/  SIFIVE_SERIAL_TXDATA_OFFS ; 
 int __ssp_readl (struct sifive_serial_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sifive_serial_is_txfifo_full(struct sifive_serial_port *ssp)
{
	return __ssp_readl(ssp, SIFIVE_SERIAL_TXDATA_OFFS) &
		SIFIVE_SERIAL_TXDATA_FULL_MASK;
}