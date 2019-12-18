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
typedef  int u16 ;
typedef  enum xgene_ring_owner { ____Placeholder_xgene_ring_owner } xgene_ring_owner ;

/* Variables and functions */
 int RING_OWNER_MASK ; 

__attribute__((used)) static inline enum xgene_ring_owner xgene_enet_ring_owner(u16 id)
{
	return (id & RING_OWNER_MASK) >> 6;
}