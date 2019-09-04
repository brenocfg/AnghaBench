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
typedef  size_t u8 ;
typedef  scalar_t__ u16 ;
struct i40e_pf {int pending_udp_bitmap; TYPE_1__* udp_ports; } ;
struct TYPE_2__ {scalar_t__ port; } ;

/* Variables and functions */
 int BIT_ULL (size_t) ; 
 size_t I40E_MAX_PF_UDP_OFFLOAD_PORTS ; 

__attribute__((used)) static u8 i40e_get_udp_port_idx(struct i40e_pf *pf, u16 port)
{
	u8 i;

	for (i = 0; i < I40E_MAX_PF_UDP_OFFLOAD_PORTS; i++) {
		/* Do not report ports with pending deletions as
		 * being available.
		 */
		if (!port && (pf->pending_udp_bitmap & BIT_ULL(i)))
			continue;
		if (pf->udp_ports[i].port == port)
			return i;
	}

	return i;
}