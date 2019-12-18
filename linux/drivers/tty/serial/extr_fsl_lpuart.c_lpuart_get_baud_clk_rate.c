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
struct lpuart_port {int /*<<< orphan*/  ipg_clk; int /*<<< orphan*/  baud_clk; } ;

/* Variables and functions */
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 scalar_t__ is_imx8qxp_lpuart (struct lpuart_port*) ; 

__attribute__((used)) static unsigned int lpuart_get_baud_clk_rate(struct lpuart_port *sport)
{
	if (is_imx8qxp_lpuart(sport))
		return clk_get_rate(sport->baud_clk);

	return clk_get_rate(sport->ipg_clk);
}