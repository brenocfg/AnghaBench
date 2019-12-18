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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 scalar_t__ RING_BUFNUM_BUFPOOL ; 
 scalar_t__ xgene_enet_is_bufpool (int /*<<< orphan*/ ) ; 
 scalar_t__ xgene_enet_ring_bufnum (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 xgene_enet_get_fpsel(u16 id)
{
	if (xgene_enet_is_bufpool(id))
		return xgene_enet_ring_bufnum(id) - RING_BUFNUM_BUFPOOL;

	return 0;
}