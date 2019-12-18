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
typedef  scalar_t__ u16 ;
struct sifive_serial_port {int /*<<< orphan*/  baud_rate; int /*<<< orphan*/  clkin_rate; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIFIVE_SERIAL_DIV_OFFS ; 
 int /*<<< orphan*/  __ssp_writel (scalar_t__,int /*<<< orphan*/ ,struct sifive_serial_port*) ; 

__attribute__((used)) static void __ssp_update_div(struct sifive_serial_port *ssp)
{
	u16 div;

	div = DIV_ROUND_UP(ssp->clkin_rate, ssp->baud_rate) - 1;

	__ssp_writel(div, SIFIVE_SERIAL_DIV_OFFS, ssp);
}