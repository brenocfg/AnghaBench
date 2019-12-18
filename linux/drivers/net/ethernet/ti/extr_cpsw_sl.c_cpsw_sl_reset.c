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
struct cpsw_sl {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_SL_SOFT_RESET ; 
 int CPSW_SL_SOFT_RESET_BIT ; 
 int cpsw_sl_reg_read (struct cpsw_sl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_sl_reg_write (struct cpsw_sl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned long) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

void cpsw_sl_reset(struct cpsw_sl *sl, unsigned long tmo)
{
	unsigned long timeout = jiffies + msecs_to_jiffies(tmo);

	/* Set the soft reset bit */
	cpsw_sl_reg_write(sl, CPSW_SL_SOFT_RESET, CPSW_SL_SOFT_RESET_BIT);

	/* Wait for the bit to clear */
	do {
		usleep_range(100, 200);
	} while ((cpsw_sl_reg_read(sl, CPSW_SL_SOFT_RESET) &
		  CPSW_SL_SOFT_RESET_BIT) &&
		  time_after(timeout, jiffies));

	if (cpsw_sl_reg_read(sl, CPSW_SL_SOFT_RESET) & CPSW_SL_SOFT_RESET_BIT)
		dev_err(sl->dev, "cpsw_sl failed to soft-reset.\n");
}