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
struct seq_file {int dummy; } ;
struct pinctrl_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_SHOW_FLAG (unsigned long) ; 
 int /*<<< orphan*/  DBG_SHOW_FLAG_MASKED (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned long DEBOUNCE ; 
 unsigned long DEBOUNCE_VAL_SHIFT ; 
 unsigned long DEGLITCH ; 
 unsigned long DIS_SCHMIT ; 
 int /*<<< orphan*/  DRIVE_STRENGTH ; 
 int /*<<< orphan*/  DRIVE_STRENGTH_BIT_MSK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRIVE_STRENGTH_HI ; 
 int /*<<< orphan*/  DRIVE_STRENGTH_LOW ; 
 int /*<<< orphan*/  DRIVE_STRENGTH_MED ; 
 int /*<<< orphan*/  HI ; 
 int /*<<< orphan*/  LOW ; 
 int /*<<< orphan*/  MED ; 
 unsigned long MULTI_DRIVE ; 
 unsigned long PULL_DOWN ; 
 unsigned long PULL_UP ; 
 unsigned long SLEWRATE ; 
 int /*<<< orphan*/  at91_pinconf_get (struct pinctrl_dev*,unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 

__attribute__((used)) static void at91_pinconf_dbg_show(struct pinctrl_dev *pctldev,
				   struct seq_file *s, unsigned pin_id)
{
	unsigned long config;
	int val, num_conf = 0;

	at91_pinconf_get(pctldev, pin_id, &config);

	DBG_SHOW_FLAG(MULTI_DRIVE);
	DBG_SHOW_FLAG(PULL_UP);
	DBG_SHOW_FLAG(PULL_DOWN);
	DBG_SHOW_FLAG(DIS_SCHMIT);
	DBG_SHOW_FLAG(DEGLITCH);
	DBG_SHOW_FLAG_MASKED(DRIVE_STRENGTH, DRIVE_STRENGTH_BIT_MSK(LOW),
			     DRIVE_STRENGTH_LOW);
	DBG_SHOW_FLAG_MASKED(DRIVE_STRENGTH, DRIVE_STRENGTH_BIT_MSK(MED),
			     DRIVE_STRENGTH_MED);
	DBG_SHOW_FLAG_MASKED(DRIVE_STRENGTH, DRIVE_STRENGTH_BIT_MSK(HI),
			     DRIVE_STRENGTH_HI);
	DBG_SHOW_FLAG(SLEWRATE);
	DBG_SHOW_FLAG(DEBOUNCE);
	if (config & DEBOUNCE) {
		val = config >> DEBOUNCE_VAL_SHIFT;
		seq_printf(s, "(%d)", val);
	}

	return;
}