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
struct nfp_app_bpf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_BPF_MAP_CACHE_CNT ; 
 int /*<<< orphan*/  NFP_NET_DEFAULT_MTU ; 
 unsigned int max3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_bpf_cmsg_map_reply_size (struct nfp_app_bpf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_bpf_cmsg_map_req_size (struct nfp_app_bpf*,int /*<<< orphan*/ ) ; 

unsigned int nfp_bpf_ctrl_cmsg_mtu(struct nfp_app_bpf *bpf)
{
	return max3(NFP_NET_DEFAULT_MTU,
		    nfp_bpf_cmsg_map_req_size(bpf, NFP_BPF_MAP_CACHE_CNT),
		    nfp_bpf_cmsg_map_reply_size(bpf, NFP_BPF_MAP_CACHE_CNT));
}