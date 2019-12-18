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
struct sk_buff {int dummy; } ;
struct nfp_app_bpf {int dummy; } ;

/* Variables and functions */
 struct sk_buff* nfp_bpf_cmsg_alloc (struct nfp_app_bpf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfp_bpf_cmsg_map_req_size (struct nfp_app_bpf*,unsigned int) ; 

__attribute__((used)) static struct sk_buff *
nfp_bpf_cmsg_map_req_alloc(struct nfp_app_bpf *bpf, unsigned int n)
{
	return nfp_bpf_cmsg_alloc(bpf, nfp_bpf_cmsg_map_req_size(bpf, n));
}