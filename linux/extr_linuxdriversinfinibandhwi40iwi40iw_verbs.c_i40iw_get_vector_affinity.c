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
struct ib_device {int dummy; } ;
struct i40iw_msix_vector {int /*<<< orphan*/  irq; } ;
struct i40iw_device {struct i40iw_msix_vector* iw_msixtbl; scalar_t__ msix_shared; } ;
struct cpumask {int dummy; } ;

/* Variables and functions */
 struct cpumask const* irq_get_affinity_mask (int /*<<< orphan*/ ) ; 
 struct i40iw_device* to_iwdev (struct ib_device*) ; 

__attribute__((used)) static const struct cpumask *i40iw_get_vector_affinity(struct ib_device *ibdev,
						       int comp_vector)
{
	struct i40iw_device *iwdev = to_iwdev(ibdev);
	struct i40iw_msix_vector *msix_vec;

	if (iwdev->msix_shared)
		msix_vec = &iwdev->iw_msixtbl[comp_vector];
	else
		msix_vec = &iwdev->iw_msixtbl[comp_vector + 1];

	return irq_get_affinity_mask(msix_vec->irq);
}