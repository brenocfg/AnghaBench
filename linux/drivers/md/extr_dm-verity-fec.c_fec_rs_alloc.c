#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dm_verity {TYPE_1__* fec; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_2__ {int /*<<< orphan*/  roots; } ;

/* Variables and functions */
 void* init_rs_gfp (int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *fec_rs_alloc(gfp_t gfp_mask, void *pool_data)
{
	struct dm_verity *v = (struct dm_verity *)pool_data;

	return init_rs_gfp(8, 0x11d, 0, 1, v->fec->roots, gfp_mask);
}