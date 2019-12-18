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
typedef  int u32 ;
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_BUG_ON_PARANOID (int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MDIO_CTRL1 ; 
 int MDIO_CTRL1_RESET ; 
 int ef4_mdio_read (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_mdio_write (struct ef4_nic*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 

int ef4_mdio_reset_mmd(struct ef4_nic *port, int mmd,
			    int spins, int spintime)
{
	u32 ctrl;

	/* Catch callers passing values in the wrong units (or just silly) */
	EF4_BUG_ON_PARANOID(spins * spintime >= 5000);

	ef4_mdio_write(port, mmd, MDIO_CTRL1, MDIO_CTRL1_RESET);
	/* Wait for the reset bit to clear. */
	do {
		msleep(spintime);
		ctrl = ef4_mdio_read(port, mmd, MDIO_CTRL1);
		spins--;

	} while (spins && (ctrl & MDIO_CTRL1_RESET));

	return spins ? spins : -ETIMEDOUT;
}