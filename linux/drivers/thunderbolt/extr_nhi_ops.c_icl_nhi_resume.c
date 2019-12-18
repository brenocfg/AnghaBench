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
struct tb_nhi {int dummy; } ;

/* Variables and functions */
 int icl_nhi_force_power (struct tb_nhi*,int) ; 
 int /*<<< orphan*/  icl_nhi_set_ltr (struct tb_nhi*) ; 

__attribute__((used)) static int icl_nhi_resume(struct tb_nhi *nhi)
{
	int ret;

	ret = icl_nhi_force_power(nhi, true);
	if (ret)
		return ret;

	icl_nhi_set_ltr(nhi);
	return 0;
}