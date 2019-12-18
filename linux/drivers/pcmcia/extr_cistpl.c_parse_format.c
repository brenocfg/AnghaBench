#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  void* u_char ;
struct TYPE_5__ {int TupleDataLen; void** TupleData; } ;
typedef  TYPE_1__ tuple_t ;
struct TYPE_6__ {void* length; void* offset; void* edc; void* type; } ;
typedef  TYPE_2__ cistpl_format_t ;

/* Variables and functions */
 int EINVAL ; 
 void* get_unaligned_le32 (void**) ; 

__attribute__((used)) static int parse_format(tuple_t *tuple, cistpl_format_t *fmt)
{
	u_char *p;

	if (tuple->TupleDataLen < 10)
		return -EINVAL;

	p = tuple->TupleData;

	fmt->type = p[0];
	fmt->edc = p[1];
	fmt->offset = get_unaligned_le32(p + 2);
	fmt->length = get_unaligned_le32(p + 6);

	return 0;
}