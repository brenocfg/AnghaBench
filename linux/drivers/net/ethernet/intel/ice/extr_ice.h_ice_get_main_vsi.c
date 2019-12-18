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
struct ice_vsi {int dummy; } ;
struct ice_pf {struct ice_vsi** vsi; } ;

/* Variables and functions */

__attribute__((used)) static inline struct ice_vsi *ice_get_main_vsi(struct ice_pf *pf)
{
	if (pf->vsi)
		return pf->vsi[0];

	return NULL;
}