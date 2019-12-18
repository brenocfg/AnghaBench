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
struct hfi1_pportdata {int sm_trap_qp; int sa_qp; } ;

/* Variables and functions */

__attribute__((used)) static void set_linkup_defaults(struct hfi1_pportdata *ppd)
{
	ppd->sm_trap_qp = 0x0;
	ppd->sa_qp = 0x1;
}