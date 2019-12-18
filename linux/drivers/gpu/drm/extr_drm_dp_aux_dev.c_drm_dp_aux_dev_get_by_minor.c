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
struct drm_dp_aux_dev {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 int /*<<< orphan*/  aux_idr ; 
 int /*<<< orphan*/  aux_idr_mutex ; 
 struct drm_dp_aux_dev* idr_find (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  kref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct drm_dp_aux_dev *drm_dp_aux_dev_get_by_minor(unsigned index)
{
	struct drm_dp_aux_dev *aux_dev = NULL;

	mutex_lock(&aux_idr_mutex);
	aux_dev = idr_find(&aux_idr, index);
	if (!kref_get_unless_zero(&aux_dev->refcount))
		aux_dev = NULL;
	mutex_unlock(&aux_idr_mutex);

	return aux_dev;
}