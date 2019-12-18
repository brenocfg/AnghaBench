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
struct efx_udp_tunnel {scalar_t__ port; int /*<<< orphan*/  count; } ;
struct efx_nic {struct efx_ef10_nic_data* nic_data; } ;
struct efx_ef10_nic_data {struct efx_udp_tunnel* udp_tunnels; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct efx_udp_tunnel*) ; 

__attribute__((used)) static struct efx_udp_tunnel *__efx_ef10_udp_tnl_lookup_port(struct efx_nic *efx,
							     __be16 port)
{
	struct efx_ef10_nic_data *nic_data = efx->nic_data;
	size_t i;

	for (i = 0; i < ARRAY_SIZE(nic_data->udp_tunnels); ++i) {
		if (!nic_data->udp_tunnels[i].count)
			continue;
		if (nic_data->udp_tunnels[i].port == port)
			return &nic_data->udp_tunnels[i];
	}
	return NULL;
}