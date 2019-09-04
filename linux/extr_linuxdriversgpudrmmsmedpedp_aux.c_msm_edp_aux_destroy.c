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
struct edp_aux {int /*<<< orphan*/  msg_mutex; int /*<<< orphan*/  drm_aux; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_dp_aux_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void msm_edp_aux_destroy(struct device *dev, struct edp_aux *aux)
{
	if (aux) {
		drm_dp_aux_unregister(&aux->drm_aux);
		mutex_destroy(&aux->msg_mutex);
	}
}