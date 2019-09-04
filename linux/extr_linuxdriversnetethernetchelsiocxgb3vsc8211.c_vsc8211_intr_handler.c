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
struct cphy {int dummy; } ;

/* Variables and functions */
 unsigned int CFG_CHG_INTR_MASK ; 
 unsigned int INTR_MASK ; 
 int /*<<< orphan*/  MDIO_DEVAD_NONE ; 
 int /*<<< orphan*/  VSC8211_INTR_STATUS ; 
 unsigned int VSC_INTR_RX_FIFO ; 
 unsigned int VSC_INTR_TX_FIFO ; 
 int cphy_cause_fifo_error ; 
 int cphy_cause_link_change ; 
 int t3_mdio_read (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int vsc8211_intr_handler(struct cphy *cphy)
{
	unsigned int cause;
	int err, cphy_cause = 0;

	err = t3_mdio_read(cphy, MDIO_DEVAD_NONE, VSC8211_INTR_STATUS, &cause);
	if (err)
		return err;

	cause &= INTR_MASK;
	if (cause & CFG_CHG_INTR_MASK)
		cphy_cause |= cphy_cause_link_change;
	if (cause & (VSC_INTR_RX_FIFO | VSC_INTR_TX_FIFO))
		cphy_cause |= cphy_cause_fifo_error;
	return cphy_cause;
}