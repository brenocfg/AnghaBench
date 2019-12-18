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
struct nfp_app_bpf {int abi_version; } ;

/* Variables and functions */

__attribute__((used)) static void nfp_bpf_init_capabilities(struct nfp_app_bpf *bpf)
{
	bpf->abi_version = 2; /* Original BPF ABI version */
}