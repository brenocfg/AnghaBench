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
struct siena_vf {int /*<<< orphan*/  status_lock; scalar_t__ status_addr; } ;

/* Variables and functions */
 int VFDI_RC_SUCCESS ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int efx_vfdi_clear_status_page(struct siena_vf *vf)
{
	mutex_lock(&vf->status_lock);
	vf->status_addr = 0;
	mutex_unlock(&vf->status_lock);

	return VFDI_RC_SUCCESS;
}