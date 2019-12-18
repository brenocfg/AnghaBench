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
typedef  int u16 ;
struct nfp_tun_mac_addr_offload {int /*<<< orphan*/  addr; void* index; void* count; void* flags; } ;
struct nfp_app {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_TYPE_TUN_MAC ; 
 int NFP_TUN_MAC_OFFLOAD_DEL_FLAG ; 
 void* cpu_to_be16 (int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct nfp_tun_mac_addr_offload*,int /*<<< orphan*/ ,int) ; 
 int nfp_flower_xmit_tun_conf (struct nfp_app*,int /*<<< orphan*/ ,int,struct nfp_tun_mac_addr_offload*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__nfp_tunnel_offload_mac(struct nfp_app *app, u8 *mac, u16 idx, bool del)
{
	struct nfp_tun_mac_addr_offload payload;

	memset(&payload, 0, sizeof(payload));

	if (del)
		payload.flags = cpu_to_be16(NFP_TUN_MAC_OFFLOAD_DEL_FLAG);

	/* FW supports multiple MACs per cmsg but restrict to single. */
	payload.count = cpu_to_be16(1);
	payload.index = cpu_to_be16(idx);
	ether_addr_copy(payload.addr, mac);

	return nfp_flower_xmit_tun_conf(app, NFP_FLOWER_CMSG_TYPE_TUN_MAC,
					sizeof(struct nfp_tun_mac_addr_offload),
					&payload, GFP_KERNEL);
}