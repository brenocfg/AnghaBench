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
struct TYPE_2__ {int /*<<< orphan*/  product_name; int /*<<< orphan*/  manufacturer; } ;
struct fmc_device {TYPE_1__ id; int /*<<< orphan*/  mezzanine_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void fmc_free_id_info(struct fmc_device *fmc)
{
	kfree(fmc->mezzanine_name);
	kfree(fmc->id.manufacturer);
	kfree(fmc->id.product_name);
}