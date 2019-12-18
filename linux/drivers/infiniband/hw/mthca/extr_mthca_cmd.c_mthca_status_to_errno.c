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
typedef  size_t u8 ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
#define  EAGAIN 154 
#define  EBADF 153 
#define  EBADMSG 152 
#define  EBUSY 151 
#define  EFAULT 150 
#define  EINVAL 149 
#define  EIO 148 
#define  ENOMEM 147 
#define  ENXIO 146 
#define  EPERM 145 
#define  MTHCA_CMD_STAT_BAD_INDEX 144 
#define  MTHCA_CMD_STAT_BAD_NVMEM 143 
#define  MTHCA_CMD_STAT_BAD_OP 142 
#define  MTHCA_CMD_STAT_BAD_PARAM 141 
#define  MTHCA_CMD_STAT_BAD_PKT 140 
#define  MTHCA_CMD_STAT_BAD_QPEE_STATE 139 
#define  MTHCA_CMD_STAT_BAD_RESOURCE 138 
#define  MTHCA_CMD_STAT_BAD_RES_STATE 137 
#define  MTHCA_CMD_STAT_BAD_SEG_PARAM 136 
#define  MTHCA_CMD_STAT_BAD_SIZE 135 
#define  MTHCA_CMD_STAT_BAD_SYS_STATE 134 
#define  MTHCA_CMD_STAT_DDR_MEM_ERR 133 
#define  MTHCA_CMD_STAT_EXCEED_LIM 132 
#define  MTHCA_CMD_STAT_INTERNAL_ERR 131 
#define  MTHCA_CMD_STAT_LAM_NOT_PRE 130 
 size_t MTHCA_CMD_STAT_OK ; 
#define  MTHCA_CMD_STAT_REG_BOUND 129 
#define  MTHCA_CMD_STAT_RESOURCE_BUSY 128 

__attribute__((used)) static int mthca_status_to_errno(u8 status)
{
	static const int trans_table[] = {
		[MTHCA_CMD_STAT_INTERNAL_ERR]   = -EIO,
		[MTHCA_CMD_STAT_BAD_OP]         = -EPERM,
		[MTHCA_CMD_STAT_BAD_PARAM]      = -EINVAL,
		[MTHCA_CMD_STAT_BAD_SYS_STATE]  = -ENXIO,
		[MTHCA_CMD_STAT_BAD_RESOURCE]   = -EBADF,
		[MTHCA_CMD_STAT_RESOURCE_BUSY]  = -EBUSY,
		[MTHCA_CMD_STAT_DDR_MEM_ERR]    = -ENOMEM,
		[MTHCA_CMD_STAT_EXCEED_LIM]     = -ENOMEM,
		[MTHCA_CMD_STAT_BAD_RES_STATE]  = -EBADF,
		[MTHCA_CMD_STAT_BAD_INDEX]      = -EBADF,
		[MTHCA_CMD_STAT_BAD_NVMEM]      = -EFAULT,
		[MTHCA_CMD_STAT_BAD_QPEE_STATE] = -EINVAL,
		[MTHCA_CMD_STAT_BAD_SEG_PARAM]  = -EFAULT,
		[MTHCA_CMD_STAT_REG_BOUND]      = -EBUSY,
		[MTHCA_CMD_STAT_LAM_NOT_PRE]    = -EAGAIN,
		[MTHCA_CMD_STAT_BAD_PKT]        = -EBADMSG,
		[MTHCA_CMD_STAT_BAD_SIZE]       = -ENOMEM,
	};

	if (status >= ARRAY_SIZE(trans_table) ||
			(status != MTHCA_CMD_STAT_OK
			 && trans_table[status] == 0))
		return -EINVAL;

	return trans_table[status];
}