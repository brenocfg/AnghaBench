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
struct TYPE_5__ {int TupleDataLen; int /*<<< orphan*/  TupleData; } ;
typedef  TYPE_1__ tuple_t ;
struct TYPE_6__ {int /*<<< orphan*/  addr; } ;
typedef  TYPE_2__ cistpl_longlink_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  get_unaligned_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int parse_longlink(tuple_t *tuple, cistpl_longlink_t *link)
{
	if (tuple->TupleDataLen < 4)
		return -EINVAL;
	link->addr = get_unaligned_le32(tuple->TupleData);
	return 0;
}