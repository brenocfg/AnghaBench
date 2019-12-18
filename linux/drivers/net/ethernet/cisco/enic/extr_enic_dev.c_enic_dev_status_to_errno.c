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
 int EFAULT ; 
 int EINPROGRESS ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
#define  ERR_EBADSTATE 140 
#define  ERR_EBUSY 139 
#define  ERR_ECMDUNKNOWN 138 
#define  ERR_EFAULT 137 
#define  ERR_EINPROGRESS 136 
#define  ERR_EINVAL 135 
#define  ERR_ELINKDOWN 134 
#define  ERR_EMAXRES 133 
#define  ERR_ENOMEM 132 
#define  ERR_ENOTSUPPORTED 131 
#define  ERR_EPERM 130 
#define  ERR_ETIMEDOUT 129 
#define  ERR_SUCCESS 128 
 int ETIMEDOUT ; 

int enic_dev_status_to_errno(int devcmd_status)
{
	switch (devcmd_status) {
	case ERR_SUCCESS:
		return 0;
	case ERR_EINVAL:
		return -EINVAL;
	case ERR_EFAULT:
		return -EFAULT;
	case ERR_EPERM:
		return -EPERM;
	case ERR_EBUSY:
		return -EBUSY;
	case ERR_ECMDUNKNOWN:
	case ERR_ENOTSUPPORTED:
		return -EOPNOTSUPP;
	case ERR_EBADSTATE:
		return -EINVAL;
	case ERR_ENOMEM:
		return -ENOMEM;
	case ERR_ETIMEDOUT:
		return -ETIMEDOUT;
	case ERR_ELINKDOWN:
		return -ENETDOWN;
	case ERR_EINPROGRESS:
		return -EINPROGRESS;
	case ERR_EMAXRES:
	default:
		return (devcmd_status < 0) ? devcmd_status : -1;
	}
}