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
struct qlcnic_dcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  qlcnic_dcb_get_cee_cfg (struct qlcnic_dcb*) ; 
 int /*<<< orphan*/  qlcnic_dcb_get_hw_capability (struct qlcnic_dcb*) ; 

__attribute__((used)) static void __qlcnic_dcb_get_info(struct qlcnic_dcb *dcb)
{
	qlcnic_dcb_get_hw_capability(dcb);
	qlcnic_dcb_get_cee_cfg(dcb);
}