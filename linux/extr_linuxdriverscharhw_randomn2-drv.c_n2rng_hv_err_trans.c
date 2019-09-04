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
 int EAGAIN ; 
 int EBUSY ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int EPERM ; 
#define  HV_EBADALIGN 134 
#define  HV_EBUSY 133 
#define  HV_EIO 132 
#define  HV_ENOACCESS 131 
#define  HV_ENORADDR 130 
#define  HV_EOK 129 
#define  HV_EWOULDBLOCK 128 

__attribute__((used)) static int n2rng_hv_err_trans(unsigned long hv_err)
{
	switch (hv_err) {
	case HV_EOK:
		return 0;
	case HV_EWOULDBLOCK:
		return -EAGAIN;
	case HV_ENOACCESS:
		return -EPERM;
	case HV_EIO:
		return -EIO;
	case HV_EBUSY:
		return -EBUSY;
	case HV_EBADALIGN:
	case HV_ENORADDR:
		return -EFAULT;
	default:
		return -EINVAL;
	}
}