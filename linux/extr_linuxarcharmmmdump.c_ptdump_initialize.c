#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  start_address; } ;
struct TYPE_6__ {unsigned int num; TYPE_1__* bits; TYPE_1__* nx_bit; TYPE_1__* ro_bit; int /*<<< orphan*/  mask; } ;
struct TYPE_5__ {scalar_t__ nx_bit; scalar_t__ ro_bit; int /*<<< orphan*/  mask; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  VMALLOC_START ; 
 TYPE_3__* address_markers ; 
 TYPE_2__* pg_level ; 

__attribute__((used)) static void ptdump_initialize(void)
{
	unsigned i, j;

	for (i = 0; i < ARRAY_SIZE(pg_level); i++)
		if (pg_level[i].bits)
			for (j = 0; j < pg_level[i].num; j++) {
				pg_level[i].mask |= pg_level[i].bits[j].mask;
				if (pg_level[i].bits[j].ro_bit)
					pg_level[i].ro_bit = &pg_level[i].bits[j];
				if (pg_level[i].bits[j].nx_bit)
					pg_level[i].nx_bit = &pg_level[i].bits[j];
			}

	address_markers[2].start_address = VMALLOC_START;
}