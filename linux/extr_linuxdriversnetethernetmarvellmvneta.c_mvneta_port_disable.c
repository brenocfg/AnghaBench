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
typedef  int /*<<< orphan*/  u32 ;
struct mvneta_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MVNETA_GMAC0_PORT_ENABLE ; 
 int /*<<< orphan*/  MVNETA_GMAC_CTRL_0 ; 
 int /*<<< orphan*/  mvreg_read (struct mvneta_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mvreg_write (struct mvneta_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mvneta_port_disable(struct mvneta_port *pp)
{
	u32 val;

	/* Reset the Enable bit in the Serial Control Register */
	val = mvreg_read(pp, MVNETA_GMAC_CTRL_0);
	val &= ~MVNETA_GMAC0_PORT_ENABLE;
	mvreg_write(pp, MVNETA_GMAC_CTRL_0, val);

	udelay(200);
}