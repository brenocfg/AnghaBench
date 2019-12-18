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
struct nfp_ccm {scalar_t__ tag_alloc_next; scalar_t__ tag_alloc_last; } ;

/* Variables and functions */
 scalar_t__ NFP_CCM_TAG_ALLOC_SPAN ; 

__attribute__((used)) static bool nfp_ccm_all_tags_busy(struct nfp_ccm *ccm)
{
	u16 used_tags;

	used_tags = ccm->tag_alloc_next - ccm->tag_alloc_last;

	return used_tags > NFP_CCM_TAG_ALLOC_SPAN;
}