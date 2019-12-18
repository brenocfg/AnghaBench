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
typedef  int u8 ;

/* Variables and functions */
#define  EFA_ADMIN_BAD_OPCODE 134 
#define  EFA_ADMIN_ILLEGAL_PARAMETER 133 
#define  EFA_ADMIN_MALFORMED_REQUEST 132 
#define  EFA_ADMIN_RESOURCE_ALLOCATION_FAILURE 131 
#define  EFA_ADMIN_SUCCESS 130 
#define  EFA_ADMIN_UNKNOWN_ERROR 129 
#define  EFA_ADMIN_UNSUPPORTED_OPCODE 128 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 

__attribute__((used)) static int efa_com_comp_status_to_errno(u8 comp_status)
{
	switch (comp_status) {
	case EFA_ADMIN_SUCCESS:
		return 0;
	case EFA_ADMIN_RESOURCE_ALLOCATION_FAILURE:
		return -ENOMEM;
	case EFA_ADMIN_UNSUPPORTED_OPCODE:
		return -EOPNOTSUPP;
	case EFA_ADMIN_BAD_OPCODE:
	case EFA_ADMIN_MALFORMED_REQUEST:
	case EFA_ADMIN_ILLEGAL_PARAMETER:
	case EFA_ADMIN_UNKNOWN_ERROR:
		return -EINVAL;
	default:
		return -EINVAL;
	}
}