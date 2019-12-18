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
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  efuse_reg_ctrl (struct _adapter*,int) ; 

void r8712_efuse_reg_uninit(struct _adapter *adapter)
{
	efuse_reg_ctrl(adapter, false);
}