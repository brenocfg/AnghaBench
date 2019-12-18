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
typedef  int u64 ;
struct TYPE_3__ {int size; int id; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* dist_fields ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 

void dpaa2_eth_cls_trim_rule(void *key_mem, u64 fields)
{
	int off = 0, new_off = 0;
	int i, size;

	for (i = 0; i < ARRAY_SIZE(dist_fields); i++) {
		size = dist_fields[i].size;
		if (dist_fields[i].id & fields) {
			memcpy(key_mem + new_off, key_mem + off, size);
			new_off += size;
		}
		off += size;
	}
}