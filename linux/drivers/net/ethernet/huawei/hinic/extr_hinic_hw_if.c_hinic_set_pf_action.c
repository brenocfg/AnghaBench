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
struct hinic_hwif {int dummy; } ;
typedef  enum hinic_pf_action { ____Placeholder_hinic_pf_action } hinic_pf_action ;

/* Variables and functions */
 int /*<<< orphan*/  HINIC_CSR_FUNC_ATTR5_ADDR ; 
 int /*<<< orphan*/  HINIC_FA5_CLEAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINIC_FA5_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PF_ACTION ; 
 int /*<<< orphan*/  hinic_hwif_read_reg (struct hinic_hwif*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hinic_hwif_write_reg (struct hinic_hwif*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hinic_set_pf_action(struct hinic_hwif *hwif, enum hinic_pf_action action)
{
	u32 attr5 = hinic_hwif_read_reg(hwif, HINIC_CSR_FUNC_ATTR5_ADDR);

	attr5 = HINIC_FA5_CLEAR(attr5, PF_ACTION);
	attr5 |= HINIC_FA5_SET(action, PF_ACTION);

	hinic_hwif_write_reg(hwif, HINIC_CSR_FUNC_ATTR5_ADDR, attr5);
}