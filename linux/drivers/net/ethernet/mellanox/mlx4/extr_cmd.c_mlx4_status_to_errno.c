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
#define  CMD_STAT_BAD_INDEX 156 
#define  CMD_STAT_BAD_NVMEM 155 
#define  CMD_STAT_BAD_OP 154 
#define  CMD_STAT_BAD_PARAM 153 
#define  CMD_STAT_BAD_PKT 152 
#define  CMD_STAT_BAD_QP_STATE 151 
#define  CMD_STAT_BAD_RESOURCE 150 
#define  CMD_STAT_BAD_RES_STATE 149 
#define  CMD_STAT_BAD_SEG_PARAM 148 
#define  CMD_STAT_BAD_SIZE 147 
#define  CMD_STAT_BAD_SYS_STATE 146 
#define  CMD_STAT_EXCEED_LIM 145 
#define  CMD_STAT_ICM_ERROR 144 
#define  CMD_STAT_INTERNAL_ERR 143 
#define  CMD_STAT_LAM_NOT_PRE 142 
#define  CMD_STAT_MULTI_FUNC_REQ 141 
 size_t CMD_STAT_OK ; 
#define  CMD_STAT_REG_BOUND 140 
#define  CMD_STAT_RESOURCE_BUSY 139 
#define  EACCES 138 
#define  EAGAIN 137 
#define  EBADF 136 
#define  EBUSY 135 
#define  EFAULT 134 
#define  EINVAL 133 
#define  EIO 132 
#define  ENFILE 131 
#define  ENOMEM 130 
#define  ENXIO 129 
#define  EPERM 128 

__attribute__((used)) static int mlx4_status_to_errno(u8 status)
{
	static const int trans_table[] = {
		[CMD_STAT_INTERNAL_ERR]	  = -EIO,
		[CMD_STAT_BAD_OP]	  = -EPERM,
		[CMD_STAT_BAD_PARAM]	  = -EINVAL,
		[CMD_STAT_BAD_SYS_STATE]  = -ENXIO,
		[CMD_STAT_BAD_RESOURCE]	  = -EBADF,
		[CMD_STAT_RESOURCE_BUSY]  = -EBUSY,
		[CMD_STAT_EXCEED_LIM]	  = -ENOMEM,
		[CMD_STAT_BAD_RES_STATE]  = -EBADF,
		[CMD_STAT_BAD_INDEX]	  = -EBADF,
		[CMD_STAT_BAD_NVMEM]	  = -EFAULT,
		[CMD_STAT_ICM_ERROR]	  = -ENFILE,
		[CMD_STAT_BAD_QP_STATE]   = -EINVAL,
		[CMD_STAT_BAD_SEG_PARAM]  = -EFAULT,
		[CMD_STAT_REG_BOUND]	  = -EBUSY,
		[CMD_STAT_LAM_NOT_PRE]	  = -EAGAIN,
		[CMD_STAT_BAD_PKT]	  = -EINVAL,
		[CMD_STAT_BAD_SIZE]	  = -ENOMEM,
		[CMD_STAT_MULTI_FUNC_REQ] = -EACCES,
	};

	if (status >= ARRAY_SIZE(trans_table) ||
	    (status != CMD_STAT_OK && trans_table[status] == 0))
		return -EIO;

	return trans_table[status];
}