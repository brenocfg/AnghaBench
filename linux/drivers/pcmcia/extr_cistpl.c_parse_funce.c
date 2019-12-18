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
struct TYPE_5__ {int TupleDataLen; scalar_t__ TupleData; } ;
typedef  TYPE_1__ tuple_t ;
struct TYPE_6__ {void** data; void* type; } ;
typedef  TYPE_2__ cistpl_funce_t ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int parse_funce(tuple_t *tuple, cistpl_funce_t *f)
{
	u_char *p;
	int i;
	if (tuple->TupleDataLen < 1)
		return -EINVAL;
	p = (u_char *)tuple->TupleData;
	f->type = p[0];
	for (i = 1; i < tuple->TupleDataLen; i++)
		f->data[i-1] = p[i];
	return 0;
}