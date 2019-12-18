#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct platform_device {int /*<<< orphan*/  id; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev_index; } ;
struct msi_desc {TYPE_1__ inta; int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {int /*<<< orphan*/  hwirq; struct msi_desc* desc; } ;
typedef  TYPE_2__ msi_alloc_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  TO_HWIRQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct platform_device* to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_sci_inta_msi_set_desc(msi_alloc_info_t *arg,
				     struct msi_desc *desc)
{
	struct platform_device *pdev = to_platform_device(desc->dev);

	arg->desc = desc;
	arg->hwirq = TO_HWIRQ(pdev->id, desc->inta.dev_index);
}