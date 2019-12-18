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
typedef  int /*<<< orphan*/  u8 ;
struct nfp_crypto_req_add_front {int /*<<< orphan*/  ipver_vlan; } ;

/* Variables and functions */
 int FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_NET_TLS_IPVER ; 
 int /*<<< orphan*/  NFP_NET_TLS_VLAN ; 
 int /*<<< orphan*/  NFP_NET_TLS_VLAN_UNUSED ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 

__attribute__((used)) static void
nfp_net_tls_set_ipver_vlan(struct nfp_crypto_req_add_front *front, u8 ipver)
{
	front->ipver_vlan = cpu_to_be16(FIELD_PREP(NFP_NET_TLS_IPVER, ipver) |
					FIELD_PREP(NFP_NET_TLS_VLAN,
						   NFP_NET_TLS_VLAN_UNUSED));
}