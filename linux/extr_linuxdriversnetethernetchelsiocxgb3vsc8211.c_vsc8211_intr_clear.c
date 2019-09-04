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
struct cphy {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_DEVAD_NONE ; 
 int /*<<< orphan*/  VSC8211_INTR_STATUS ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vsc8211_intr_clear(struct cphy *cphy)
{
	u32 val;

	/* Clear PHY interrupts by reading the register. */
	return t3_mdio_read(cphy, MDIO_DEVAD_NONE, VSC8211_INTR_STATUS, &val);
}