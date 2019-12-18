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
struct i40e_pf {size_t iwarp_base_vector; int /*<<< orphan*/ * msix_entries; int /*<<< orphan*/  num_iwarp_msix; struct i40e_client_instance* cinst; } ;
struct TYPE_2__ {int /*<<< orphan*/ * msix_entries; int /*<<< orphan*/  msix_count; } ;
struct i40e_client_instance {TYPE_1__ lan_info; int /*<<< orphan*/  client; } ;

/* Variables and functions */

void i40e_client_update_msix_info(struct i40e_pf *pf)
{
	struct i40e_client_instance *cdev = pf->cinst;

	if (!cdev || !cdev->client)
		return;

	cdev->lan_info.msix_count = pf->num_iwarp_msix;
	cdev->lan_info.msix_entries = &pf->msix_entries[pf->iwarp_base_vector];
}