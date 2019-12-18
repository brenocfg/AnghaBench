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
typedef  enum nfp_ccm_type { ____Placeholder_nfp_ccm_type } nfp_ccm_type ;

/* Variables and functions */
 int NFP_CCM_TYPE_BPF_MAP_GETFIRST ; 
 int NFP_CCM_TYPE_BPF_MAP_GETNEXT ; 

__attribute__((used)) static bool nfp_bpf_ctrl_op_cache_fill(enum nfp_ccm_type op)
{
	return op == NFP_CCM_TYPE_BPF_MAP_GETFIRST ||
	       op == NFP_CCM_TYPE_BPF_MAP_GETNEXT;
}