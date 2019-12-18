#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct slic_device {scalar_t__ is_fiber; TYPE_1__* pdev; } ;
struct TYPE_2__ {unsigned int subsystem_device; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int ADVERTISE_1000XFULL ; 
 int ADVERTISE_1000XPAUSE ; 
 int ADVERTISE_1000XPSE_ASYM ; 
 int ADVERTISE_100FULL ; 
 int ADVERTISE_100HALF ; 
 int ADVERTISE_10FULL ; 
 int ADVERTISE_10HALF ; 
 int ADVERTISE_CSMA ; 
 int ADVERTISE_PAUSE_ASYM ; 
 int ADVERTISE_PAUSE_CAP ; 
 int BMCR_ANENABLE ; 
 int BMCR_ANRESTART ; 
 int BMCR_RESET ; 
 int MII_ADVERTISE ; 
 int MII_BMCR ; 
 int MII_CTRL1000 ; 
 unsigned int PCI_SUBDEVICE_ID_ALACRITECH_CICADA ; 
 int SLIC_MIICR_REG_16 ; 
 int SLIC_MRV_REG16_XOVERON ; 
 int /*<<< orphan*/  SLIC_REG_WPHY ; 
 int /*<<< orphan*/  slic_write (struct slic_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void slic_set_link_autoneg(struct slic_device *sdev)
{
	unsigned int subid = sdev->pdev->subsystem_device;
	u32 val;

	if (sdev->is_fiber) {
		/* We've got a fiber gigabit interface, and register 4 is
		 * different in fiber mode than in copper mode.
		 */
		/* advertise FD only @1000 Mb */
		val = MII_ADVERTISE << 16 | ADVERTISE_1000XFULL |
		      ADVERTISE_1000XPAUSE | ADVERTISE_1000XPSE_ASYM;
		/* enable PAUSE frames */
		slic_write(sdev, SLIC_REG_WPHY, val);
		/* reset phy, enable auto-neg  */
		val = MII_BMCR << 16 | BMCR_RESET | BMCR_ANENABLE |
		      BMCR_ANRESTART;
		slic_write(sdev, SLIC_REG_WPHY, val);
	} else {	/* copper gigabit */
		/* We've got a copper gigabit interface, and register 4 is
		 * different in copper mode than in fiber mode.
		 */
		/* advertise 10/100 Mb modes   */
		val = MII_ADVERTISE << 16 | ADVERTISE_100FULL |
		      ADVERTISE_100HALF | ADVERTISE_10FULL | ADVERTISE_10HALF;
		/* enable PAUSE frames  */
		val |= ADVERTISE_PAUSE_CAP | ADVERTISE_PAUSE_ASYM;
		/* required by the Cicada PHY  */
		val |= ADVERTISE_CSMA;
		slic_write(sdev, SLIC_REG_WPHY, val);

		/* advertise FD only @1000 Mb  */
		val = MII_CTRL1000 << 16 | ADVERTISE_1000FULL;
		slic_write(sdev, SLIC_REG_WPHY, val);

		if (subid != PCI_SUBDEVICE_ID_ALACRITECH_CICADA) {
			 /* if a Marvell PHY enable auto crossover */
			val = SLIC_MIICR_REG_16 | SLIC_MRV_REG16_XOVERON;
			slic_write(sdev, SLIC_REG_WPHY, val);

			/* reset phy, enable auto-neg  */
			val = MII_BMCR << 16 | BMCR_RESET | BMCR_ANENABLE |
			      BMCR_ANRESTART;
			slic_write(sdev, SLIC_REG_WPHY, val);
		} else {
			/* enable and restart auto-neg (don't reset)  */
			val = MII_BMCR << 16 | BMCR_ANENABLE | BMCR_ANRESTART;
			slic_write(sdev, SLIC_REG_WPHY, val);
		}
	}
}