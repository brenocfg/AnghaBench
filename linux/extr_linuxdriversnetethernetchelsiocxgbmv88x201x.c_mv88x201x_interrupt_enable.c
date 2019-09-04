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
struct cphy {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_INT_ENABLE ; 
 int /*<<< orphan*/  ELMER0_GP_BIT6 ; 
 int /*<<< orphan*/  MDIO_MMD_PMAPMD ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_LASI_LSALARM ; 
 int /*<<< orphan*/  cphy_mdio_write (struct cphy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ t1_is_asic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mv88x201x_interrupt_enable(struct cphy *cphy)
{
	/* Enable PHY LASI interrupts. */
	cphy_mdio_write(cphy, MDIO_MMD_PMAPMD, MDIO_PMA_LASI_CTRL,
			MDIO_PMA_LASI_LSALARM);

	/* Enable Marvell interrupts through Elmer0. */
	if (t1_is_asic(cphy->adapter)) {
		u32 elmer;

		t1_tpi_read(cphy->adapter, A_ELMER0_INT_ENABLE, &elmer);
		elmer |= ELMER0_GP_BIT6;
		t1_tpi_write(cphy->adapter, A_ELMER0_INT_ENABLE, elmer);
	}
	return 0;
}