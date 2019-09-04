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
typedef  enum obj_operation_type { ____Placeholder_obj_operation_type } obj_operation_type ;

/* Variables and functions */
#define  OBJ_OP_DISCARD 130 
#define  OBJ_OP_READ 129 
#define  OBJ_OP_WRITE 128 

__attribute__((used)) static char* obj_op_name(enum obj_operation_type op_type)
{
	switch (op_type) {
	case OBJ_OP_READ:
		return "read";
	case OBJ_OP_WRITE:
		return "write";
	case OBJ_OP_DISCARD:
		return "discard";
	default:
		return "???";
	}
}