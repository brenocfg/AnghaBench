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
struct nfp_app_bpf {unsigned int cmsg_key_sz; unsigned int cmsg_val_sz; } ;
struct cmsg_req_map_op {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int
nfp_bpf_cmsg_map_req_size(struct nfp_app_bpf *bpf, unsigned int n)
{
	unsigned int size;

	size = sizeof(struct cmsg_req_map_op);
	size += (bpf->cmsg_key_sz + bpf->cmsg_val_sz) * n;

	return size;
}