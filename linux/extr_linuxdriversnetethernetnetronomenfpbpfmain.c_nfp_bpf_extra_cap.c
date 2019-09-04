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
struct nfp_net {int dummy; } ;
struct nfp_app {int dummy; } ;

/* Variables and functions */
 scalar_t__ nfp_net_ebpf_capable (struct nfp_net*) ; 

__attribute__((used)) static const char *nfp_bpf_extra_cap(struct nfp_app *app, struct nfp_net *nn)
{
	return nfp_net_ebpf_capable(nn) ? "BPF" : "";
}