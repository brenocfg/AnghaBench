#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct TYPE_7__ {int TupleDataLen; scalar_t__ TupleData; } ;
typedef  TYPE_2__ tuple_t ;
struct TYPE_8__ {int ngeo; TYPE_1__* geo; } ;
typedef  TYPE_3__ cistpl_device_geo_t ;
struct TYPE_6__ {int buswidth; int erase_block; int read_block; int write_block; int partition; int interleave; } ;

/* Variables and functions */
 int CISTPL_MAX_DEVICES ; 

__attribute__((used)) static int parse_device_geo(tuple_t *tuple, cistpl_device_geo_t *geo)
{
	u_char *p, *q;
	int n;

	p = (u_char *)tuple->TupleData;
	q = p + tuple->TupleDataLen;

	for (n = 0; n < CISTPL_MAX_DEVICES; n++) {
		if (p > q-6)
			break;
		geo->geo[n].buswidth = p[0];
		geo->geo[n].erase_block = 1 << (p[1]-1);
		geo->geo[n].read_block  = 1 << (p[2]-1);
		geo->geo[n].write_block = 1 << (p[3]-1);
		geo->geo[n].partition   = 1 << (p[4]-1);
		geo->geo[n].interleave  = 1 << (p[5]-1);
		p += 6;
	}
	geo->ngeo = n;
	return 0;
}