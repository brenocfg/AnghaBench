#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int cls_prot; int cls_field; scalar_t__ size; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 TYPE_1__* dist_fields ; 

int dpaa2_eth_cls_fld_off(int prot, int field)
{
	int i, off = 0;

	for (i = 0; i < ARRAY_SIZE(dist_fields); i++) {
		if (dist_fields[i].cls_prot == prot &&
		    dist_fields[i].cls_field == field)
			return off;
		off += dist_fields[i].size;
	}

	WARN_ONCE(1, "Unsupported header field used for Rx flow cls\n");
	return 0;
}