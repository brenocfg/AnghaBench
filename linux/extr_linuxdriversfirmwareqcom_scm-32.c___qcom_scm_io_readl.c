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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  QCOM_SCM_IO_READ ; 
 int /*<<< orphan*/  QCOM_SCM_SVC_IO ; 
 int qcom_scm_call_atomic1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int __qcom_scm_io_readl(struct device *dev, phys_addr_t addr,
			unsigned int *val)
{
	int ret;

	ret = qcom_scm_call_atomic1(QCOM_SCM_SVC_IO, QCOM_SCM_IO_READ, addr);
	if (ret >= 0)
		*val = ret;

	return ret < 0 ? ret : 0;
}