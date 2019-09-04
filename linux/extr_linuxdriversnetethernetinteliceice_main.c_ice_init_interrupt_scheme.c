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
typedef  int /*<<< orphan*/  u16 ;
struct ice_res_tracker {int dummy; } ;
struct ice_pf {TYPE_2__* irq_tracker; TYPE_1__* pdev; int /*<<< orphan*/  flags; } ;
typedef  int ssize_t ;
struct TYPE_4__ {int num_entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ICE_FLAG_MSIX_ENA ; 
 TYPE_2__* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_dis_msix (struct ice_pf*) ; 
 int ice_ena_msix_range (struct ice_pf*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ice_init_interrupt_scheme(struct ice_pf *pf)
{
	int vectors = 0;
	ssize_t size;

	if (test_bit(ICE_FLAG_MSIX_ENA, pf->flags))
		vectors = ice_ena_msix_range(pf);
	else
		return -ENODEV;

	if (vectors < 0)
		return vectors;

	/* set up vector assignment tracking */
	size = sizeof(struct ice_res_tracker) + (sizeof(u16) * vectors);

	pf->irq_tracker = devm_kzalloc(&pf->pdev->dev, size, GFP_KERNEL);
	if (!pf->irq_tracker) {
		ice_dis_msix(pf);
		return -ENOMEM;
	}

	pf->irq_tracker->num_entries = vectors;

	return 0;
}