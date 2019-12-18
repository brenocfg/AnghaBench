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
typedef  int u16 ;

/* Variables and functions */
 int EBADR ; 
 int EINVAL ; 
 int EIO ; 
 int ENOLINK ; 
 int ENOSR ; 
 int ENOTBLK ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int ERANGE ; 
 int ETIME ; 
 int EXFULL ; 
#define  HCLGE_CMD_EXEC_SUCCESS 139 
#define  HCLGE_CMD_HILINK_ERR 138 
#define  HCLGE_CMD_INVALID 137 
#define  HCLGE_CMD_NEXT_ERR 136 
#define  HCLGE_CMD_NOT_SUPPORTED 135 
#define  HCLGE_CMD_NO_AUTH 134 
#define  HCLGE_CMD_PARA_ERR 133 
#define  HCLGE_CMD_QUEUE_FULL 132 
#define  HCLGE_CMD_QUEUE_ILLEGAL 131 
#define  HCLGE_CMD_RESULT_ERR 130 
#define  HCLGE_CMD_TIMEOUT 129 
#define  HCLGE_CMD_UNEXE_ERR 128 

__attribute__((used)) static int hclge_cmd_convert_err_code(u16 desc_ret)
{
	switch (desc_ret) {
	case HCLGE_CMD_EXEC_SUCCESS:
		return 0;
	case HCLGE_CMD_NO_AUTH:
		return -EPERM;
	case HCLGE_CMD_NOT_SUPPORTED:
		return -EOPNOTSUPP;
	case HCLGE_CMD_QUEUE_FULL:
		return -EXFULL;
	case HCLGE_CMD_NEXT_ERR:
		return -ENOSR;
	case HCLGE_CMD_UNEXE_ERR:
		return -ENOTBLK;
	case HCLGE_CMD_PARA_ERR:
		return -EINVAL;
	case HCLGE_CMD_RESULT_ERR:
		return -ERANGE;
	case HCLGE_CMD_TIMEOUT:
		return -ETIME;
	case HCLGE_CMD_HILINK_ERR:
		return -ENOLINK;
	case HCLGE_CMD_QUEUE_ILLEGAL:
		return -ENXIO;
	case HCLGE_CMD_INVALID:
		return -EBADR;
	default:
		return -EIO;
	}
}