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
struct cphy {int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_ELMER0_INT_CAUSE ; 
 int ELMER0_GP_BIT1 ; 
 int ELMER0_GP_BIT2 ; 
 int ELMER0_GP_BIT3 ; 
 int ELMER0_GP_BIT4 ; 
 int /*<<< orphan*/  MV88E1XXX_INTERRUPT_STATUS_REGISTER ; 
 scalar_t__ is_T2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_mdio_read (struct cphy*,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ t1_is_asic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t1_tpi_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  t1_tpi_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mv88e1xxx_interrupt_clear(struct cphy *cphy)
{
	u32 elmer;

	/* Clear PHY interrupts by reading the register. */
	(void) simple_mdio_read(cphy,
			MV88E1XXX_INTERRUPT_STATUS_REGISTER, &elmer);

	/* Clear Marvell interrupts through Elmer0. */
	if (t1_is_asic(cphy->adapter)) {
		t1_tpi_read(cphy->adapter, A_ELMER0_INT_CAUSE, &elmer);
		elmer |= ELMER0_GP_BIT1;
		if (is_T2(cphy->adapter))
		    elmer |= ELMER0_GP_BIT2|ELMER0_GP_BIT3|ELMER0_GP_BIT4;
		t1_tpi_write(cphy->adapter, A_ELMER0_INT_CAUSE, elmer);
	}
	return 0;
}