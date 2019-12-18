#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int* vec; } ;
struct TYPE_4__ {TYPE_1__ aprox_match; } ;
struct bnx2x_mcast_obj {int /*<<< orphan*/  (* set_registry_size ) (struct bnx2x_mcast_obj*,int) ;TYPE_2__ registry; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int BNX2X_MCAST_VEC_SZ ; 
 int /*<<< orphan*/  stub1 (struct bnx2x_mcast_obj*,int) ; 

__attribute__((used)) static inline int bnx2x_mcast_refresh_registry_e2(struct bnx2x *bp,
						  struct bnx2x_mcast_obj *o)
{
	int i, cnt = 0;
	u64 elem;

	for (i = 0; i < BNX2X_MCAST_VEC_SZ; i++) {
		elem = o->registry.aprox_match.vec[i];
		for (; elem; cnt++)
			elem &= elem - 1;
	}

	o->set_registry_size(o, cnt);

	return 0;
}