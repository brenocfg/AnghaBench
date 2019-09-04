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
typedef  scalar_t__ u16 ;
struct nfp_app_bpf {scalar_t__ tag_alloc_next; scalar_t__ tag_alloc_last; } ;

/* Variables and functions */
 scalar_t__ NFP_BPF_TAG_ALLOC_SPAN ; 

__attribute__((used)) static bool nfp_bpf_all_tags_busy(struct nfp_app_bpf *bpf)
{
	u16 used_tags;

	used_tags = bpf->tag_alloc_next - bpf->tag_alloc_last;

	return used_tags > NFP_BPF_TAG_ALLOC_SPAN;
}