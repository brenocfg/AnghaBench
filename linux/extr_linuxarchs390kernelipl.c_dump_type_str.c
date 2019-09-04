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
typedef  enum dump_type { ____Placeholder_dump_type } dump_type ;

/* Variables and functions */
 char* DUMP_CCW_STR ; 
 char* DUMP_FCP_STR ; 
 char* DUMP_NONE_STR ; 
#define  DUMP_TYPE_CCW 130 
#define  DUMP_TYPE_FCP 129 
#define  DUMP_TYPE_NONE 128 

__attribute__((used)) static char *dump_type_str(enum dump_type type)
{
	switch (type) {
	case DUMP_TYPE_NONE:
		return DUMP_NONE_STR;
	case DUMP_TYPE_CCW:
		return DUMP_CCW_STR;
	case DUMP_TYPE_FCP:
		return DUMP_FCP_STR;
	default:
		return NULL;
	}
}