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
typedef  int u16 ;
struct fm10k_hw {int dummy; } ;

/* Variables and functions */
 int FM10K_MAX_VECTORS_PF ; 
 int fm10k_vectors_per_pool (struct fm10k_hw*) ; 

__attribute__((used)) static u16 fm10k_vf_vector_index(struct fm10k_hw *hw, u16 vf_idx)
{
	u16 vf_v_idx = FM10K_MAX_VECTORS_PF;

	vf_v_idx += fm10k_vectors_per_pool(hw) * vf_idx;

	return vf_v_idx;
}