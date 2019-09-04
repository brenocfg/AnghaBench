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
struct hfi1_pportdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HFI1_IB_CFG_LWID_DG_ENB ; 
 int /*<<< orphan*/  hfi1_set_ib_cfg (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_link_width_downgrade_enabled(struct hfi1_pportdata *ppd, u32 w)
{
	(void)hfi1_set_ib_cfg(ppd, HFI1_IB_CFG_LWID_DG_ENB, w);
}