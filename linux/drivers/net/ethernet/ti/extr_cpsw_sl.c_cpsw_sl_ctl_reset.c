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
struct cpsw_sl {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_SL_MACCONTROL ; 
 int /*<<< orphan*/  cpsw_sl_reg_write (struct cpsw_sl*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cpsw_sl_ctl_reset(struct cpsw_sl *sl)
{
	cpsw_sl_reg_write(sl, CPSW_SL_MACCONTROL, 0);
}