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
 unsigned int max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_bpf_cmsg_map_reply_size (struct nfp_app_bpf*,int) ; 
 int /*<<< orphan*/  nfp_bpf_cmsg_map_req_size (struct nfp_app_bpf*,int) ; 

unsigned int nfp_bpf_ctrl_cmsg_min_mtu(struct nfp_app_bpf *bpf)
{
	return max(nfp_bpf_cmsg_map_req_size(bpf, 1),
		   nfp_bpf_cmsg_map_reply_size(bpf, 1));
}