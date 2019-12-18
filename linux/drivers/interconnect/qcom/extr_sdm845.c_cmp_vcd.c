#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ vcd; } ;
struct qcom_icc_bcm {TYPE_1__ aux_data; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_vcd(const void *_l, const void *_r)
{
	const struct qcom_icc_bcm **l = (const struct qcom_icc_bcm **)_l;
	const struct qcom_icc_bcm **r = (const struct qcom_icc_bcm **)_r;

	if (l[0]->aux_data.vcd < r[0]->aux_data.vcd)
		return -1;
	else if (l[0]->aux_data.vcd == r[0]->aux_data.vcd)
		return 0;
	else
		return 1;
}