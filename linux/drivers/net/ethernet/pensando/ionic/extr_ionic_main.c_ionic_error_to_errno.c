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
typedef  enum ionic_status_code { ____Placeholder_ionic_status_code } ionic_status_code ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EEXIST ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int EPERM ; 
 int ERANGE ; 
#define  IONIC_RC_BAD_ADDR 148 
#define  IONIC_RC_DEV_CMD 147 
#define  IONIC_RC_EAGAIN 146 
#define  IONIC_RC_EBUSY 145 
#define  IONIC_RC_EEXIST 144 
#define  IONIC_RC_EFAULT 143 
#define  IONIC_RC_EINTR 142 
#define  IONIC_RC_EINVAL 141 
#define  IONIC_RC_EIO 140 
#define  IONIC_RC_ENOENT 139 
#define  IONIC_RC_ENOMEM 138 
#define  IONIC_RC_ENOSPC 137 
#define  IONIC_RC_EOPCODE 136 
#define  IONIC_RC_EPERM 135 
#define  IONIC_RC_EQID 134 
#define  IONIC_RC_EQTYPE 133 
#define  IONIC_RC_ERANGE 132 
#define  IONIC_RC_ERDMA 131 
#define  IONIC_RC_ERROR 130 
#define  IONIC_RC_EVERSION 129 
#define  IONIC_RC_SUCCESS 128 

__attribute__((used)) static int ionic_error_to_errno(enum ionic_status_code code)
{
	switch (code) {
	case IONIC_RC_SUCCESS:
		return 0;
	case IONIC_RC_EVERSION:
	case IONIC_RC_EQTYPE:
	case IONIC_RC_EQID:
	case IONIC_RC_EINVAL:
		return -EINVAL;
	case IONIC_RC_EPERM:
		return -EPERM;
	case IONIC_RC_ENOENT:
		return -ENOENT;
	case IONIC_RC_EAGAIN:
		return -EAGAIN;
	case IONIC_RC_ENOMEM:
		return -ENOMEM;
	case IONIC_RC_EFAULT:
		return -EFAULT;
	case IONIC_RC_EBUSY:
		return -EBUSY;
	case IONIC_RC_EEXIST:
		return -EEXIST;
	case IONIC_RC_ENOSPC:
		return -ENOSPC;
	case IONIC_RC_ERANGE:
		return -ERANGE;
	case IONIC_RC_BAD_ADDR:
		return -EFAULT;
	case IONIC_RC_EOPCODE:
	case IONIC_RC_EINTR:
	case IONIC_RC_DEV_CMD:
	case IONIC_RC_ERROR:
	case IONIC_RC_ERDMA:
	case IONIC_RC_EIO:
	default:
		return -EIO;
	}
}