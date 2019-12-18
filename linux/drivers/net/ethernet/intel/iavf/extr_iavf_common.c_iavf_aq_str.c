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
struct iavf_hw {char const* err_str; } ;
typedef  enum iavf_admin_queue_err { ____Placeholder_iavf_admin_queue_err } iavf_admin_queue_err ;

/* Variables and functions */
#define  IAVF_AQ_RC_BAD_ADDR 150 
#define  IAVF_AQ_RC_E2BIG 149 
#define  IAVF_AQ_RC_EACCES 148 
#define  IAVF_AQ_RC_EAGAIN 147 
#define  IAVF_AQ_RC_EBUSY 146 
#define  IAVF_AQ_RC_EEXIST 145 
#define  IAVF_AQ_RC_EFAULT 144 
#define  IAVF_AQ_RC_EFBIG 143 
#define  IAVF_AQ_RC_EFLUSHED 142 
#define  IAVF_AQ_RC_EINTR 141 
#define  IAVF_AQ_RC_EINVAL 140 
#define  IAVF_AQ_RC_EIO 139 
#define  IAVF_AQ_RC_EMODE 138 
#define  IAVF_AQ_RC_ENOENT 137 
#define  IAVF_AQ_RC_ENOMEM 136 
#define  IAVF_AQ_RC_ENOSPC 135 
#define  IAVF_AQ_RC_ENOSYS 134 
#define  IAVF_AQ_RC_ENOTTY 133 
#define  IAVF_AQ_RC_ENXIO 132 
#define  IAVF_AQ_RC_EPERM 131 
#define  IAVF_AQ_RC_ERANGE 130 
#define  IAVF_AQ_RC_ESRCH 129 
#define  IAVF_AQ_RC_OK 128 
 int /*<<< orphan*/  snprintf (char const*,int,char*,int) ; 

const char *iavf_aq_str(struct iavf_hw *hw, enum iavf_admin_queue_err aq_err)
{
	switch (aq_err) {
	case IAVF_AQ_RC_OK:
		return "OK";
	case IAVF_AQ_RC_EPERM:
		return "IAVF_AQ_RC_EPERM";
	case IAVF_AQ_RC_ENOENT:
		return "IAVF_AQ_RC_ENOENT";
	case IAVF_AQ_RC_ESRCH:
		return "IAVF_AQ_RC_ESRCH";
	case IAVF_AQ_RC_EINTR:
		return "IAVF_AQ_RC_EINTR";
	case IAVF_AQ_RC_EIO:
		return "IAVF_AQ_RC_EIO";
	case IAVF_AQ_RC_ENXIO:
		return "IAVF_AQ_RC_ENXIO";
	case IAVF_AQ_RC_E2BIG:
		return "IAVF_AQ_RC_E2BIG";
	case IAVF_AQ_RC_EAGAIN:
		return "IAVF_AQ_RC_EAGAIN";
	case IAVF_AQ_RC_ENOMEM:
		return "IAVF_AQ_RC_ENOMEM";
	case IAVF_AQ_RC_EACCES:
		return "IAVF_AQ_RC_EACCES";
	case IAVF_AQ_RC_EFAULT:
		return "IAVF_AQ_RC_EFAULT";
	case IAVF_AQ_RC_EBUSY:
		return "IAVF_AQ_RC_EBUSY";
	case IAVF_AQ_RC_EEXIST:
		return "IAVF_AQ_RC_EEXIST";
	case IAVF_AQ_RC_EINVAL:
		return "IAVF_AQ_RC_EINVAL";
	case IAVF_AQ_RC_ENOTTY:
		return "IAVF_AQ_RC_ENOTTY";
	case IAVF_AQ_RC_ENOSPC:
		return "IAVF_AQ_RC_ENOSPC";
	case IAVF_AQ_RC_ENOSYS:
		return "IAVF_AQ_RC_ENOSYS";
	case IAVF_AQ_RC_ERANGE:
		return "IAVF_AQ_RC_ERANGE";
	case IAVF_AQ_RC_EFLUSHED:
		return "IAVF_AQ_RC_EFLUSHED";
	case IAVF_AQ_RC_BAD_ADDR:
		return "IAVF_AQ_RC_BAD_ADDR";
	case IAVF_AQ_RC_EMODE:
		return "IAVF_AQ_RC_EMODE";
	case IAVF_AQ_RC_EFBIG:
		return "IAVF_AQ_RC_EFBIG";
	}

	snprintf(hw->err_str, sizeof(hw->err_str), "%d", aq_err);
	return hw->err_str;
}