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
struct apei_resources {int /*<<< orphan*/  ioport; int /*<<< orphan*/  iomem; } ;

/* Variables and functions */
 int apei_res_sub (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int apei_resources_sub(struct apei_resources *resources1,
		       struct apei_resources *resources2)
{
	int rc;

	rc = apei_res_sub(&resources1->iomem, &resources2->iomem);
	if (rc)
		return rc;
	return apei_res_sub(&resources1->ioport, &resources2->ioport);
}