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
typedef  int /*<<< orphan*/  uint32_t ;
struct pcmcia_low_level {int first; int nr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MECR ; 
 int /*<<< orphan*/  MECR_CIT ; 
 int /*<<< orphan*/  MECR_NOS ; 
 int /*<<< orphan*/  __raw_writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_arcom_zeus () ; 
 scalar_t__ machine_is_viper () ; 

void pxa2xx_configure_sockets(struct device *dev, struct pcmcia_low_level *ops)
{
	/*
	 * We have at least one socket, so set MECR:CIT
	 * (Card Is There)
	 */
	uint32_t mecr = MECR_CIT;

	/* Set MECR:NOS (Number Of Sockets) */
	if ((ops->first + ops->nr) > 1 ||
	    machine_is_viper() || machine_is_arcom_zeus())
		mecr |= MECR_NOS;

	__raw_writel(mecr, MECR);
}