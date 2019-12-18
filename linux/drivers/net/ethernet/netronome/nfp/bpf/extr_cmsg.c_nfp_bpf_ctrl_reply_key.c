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
struct cmsg_reply_map_op {void* data; } ;

/* Variables and functions */

__attribute__((used)) static void *
nfp_bpf_ctrl_reply_key(struct nfp_app_bpf *bpf, struct cmsg_reply_map_op *reply,
		       unsigned int n)
{
	return &reply->data[bpf->cmsg_key_sz * n + bpf->cmsg_val_sz * n];
}