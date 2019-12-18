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
struct sprd_adi {scalar_t__ slave_pbase; } ;

/* Variables and functions */
 int /*<<< orphan*/  HWRST_STATUS_WATCHDOG ; 
 scalar_t__ PMIC_RST_STATUS ; 
 int /*<<< orphan*/  sprd_adi_read (struct sprd_adi*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprd_adi_write (struct sprd_adi*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sprd_adi_set_wdt_rst_mode(struct sprd_adi *sadi)
{
#ifdef CONFIG_SPRD_WATCHDOG
	u32 val;

	/* Set default watchdog reboot mode */
	sprd_adi_read(sadi, sadi->slave_pbase + PMIC_RST_STATUS, &val);
	val |= HWRST_STATUS_WATCHDOG;
	sprd_adi_write(sadi, sadi->slave_pbase + PMIC_RST_STATUS, val);
#endif
}