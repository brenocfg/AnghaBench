#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct radio_isa_card {TYPE_1__* drv; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  region_size; } ;

/* Variables and functions */
 struct radio_isa_card* dev_get_drvdata (struct device*) ; 
 int radio_isa_common_remove (struct radio_isa_card*,int /*<<< orphan*/ ) ; 

int radio_isa_remove(struct device *pdev, unsigned int dev)
{
	struct radio_isa_card *isa = dev_get_drvdata(pdev);

	return radio_isa_common_remove(isa, isa->drv->region_size);
}