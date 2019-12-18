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
struct TYPE_2__ {int /*<<< orphan*/  pd_id; } ;
struct i40iw_pd {TYPE_1__ sc_pd; int /*<<< orphan*/  usecount; } ;
struct i40iw_device {int /*<<< orphan*/  allocated_pds; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40iw_free_resource (struct i40iw_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void i40iw_rem_pdusecount(struct i40iw_pd *iwpd, struct i40iw_device *iwdev)
{
	if (!atomic_dec_and_test(&iwpd->usecount))
		return;
	i40iw_free_resource(iwdev, iwdev->allocated_pds, iwpd->sc_pd.pd_id);
}