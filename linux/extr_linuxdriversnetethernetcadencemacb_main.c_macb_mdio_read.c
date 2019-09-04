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
struct mii_bus {struct macb* priv; } ;
struct macb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CODE ; 
 int /*<<< orphan*/  DATA ; 
 int /*<<< orphan*/  IDLE ; 
 int MACB_BF (int /*<<< orphan*/ ,int) ; 
 int MACB_BFEXT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACB_MAN_CODE ; 
 int MACB_MAN_READ ; 
 int MACB_MAN_SOF ; 
 int /*<<< orphan*/  MAN ; 
 int /*<<< orphan*/  NSR ; 
 int /*<<< orphan*/  PHYA ; 
 int /*<<< orphan*/  REGA ; 
 int /*<<< orphan*/  RW ; 
 int /*<<< orphan*/  SOF ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  macb_readl (struct macb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macb_writel (struct macb*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int macb_mdio_read(struct mii_bus *bus, int mii_id, int regnum)
{
	struct macb *bp = bus->priv;
	int value;

	macb_writel(bp, MAN, (MACB_BF(SOF, MACB_MAN_SOF)
			      | MACB_BF(RW, MACB_MAN_READ)
			      | MACB_BF(PHYA, mii_id)
			      | MACB_BF(REGA, regnum)
			      | MACB_BF(CODE, MACB_MAN_CODE)));

	/* wait for end of transfer */
	while (!MACB_BFEXT(IDLE, macb_readl(bp, NSR)))
		cpu_relax();

	value = MACB_BFEXT(DATA, macb_readl(bp, MAN));

	return value;
}