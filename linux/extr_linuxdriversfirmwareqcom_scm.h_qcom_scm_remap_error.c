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

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
#define  QCOM_SCM_EINVAL_ADDR 133 
#define  QCOM_SCM_EINVAL_ARG 132 
#define  QCOM_SCM_ENOMEM 131 
#define  QCOM_SCM_EOPNOTSUPP 130 
#define  QCOM_SCM_ERROR 129 
#define  QCOM_SCM_V2_EBUSY 128 

__attribute__((used)) static inline int qcom_scm_remap_error(int err)
{
	switch (err) {
	case QCOM_SCM_ERROR:
		return -EIO;
	case QCOM_SCM_EINVAL_ADDR:
	case QCOM_SCM_EINVAL_ARG:
		return -EINVAL;
	case QCOM_SCM_EOPNOTSUPP:
		return -EOPNOTSUPP;
	case QCOM_SCM_ENOMEM:
		return -ENOMEM;
	case QCOM_SCM_V2_EBUSY:
		return -EBUSY;
	}
	return -EINVAL;
}