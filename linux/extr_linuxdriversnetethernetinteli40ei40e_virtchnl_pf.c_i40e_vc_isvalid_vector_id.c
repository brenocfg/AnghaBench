#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct i40e_vf {struct i40e_pf* pf; } ;
struct TYPE_3__ {scalar_t__ num_msix_vectors_vf; } ;
struct TYPE_4__ {TYPE_1__ func_caps; } ;
struct i40e_pf {TYPE_2__ hw; } ;

/* Variables and functions */

__attribute__((used)) static inline bool i40e_vc_isvalid_vector_id(struct i40e_vf *vf, u8 vector_id)
{
	struct i40e_pf *pf = vf->pf;

	return vector_id < pf->hw.func_caps.num_msix_vectors_vf;
}