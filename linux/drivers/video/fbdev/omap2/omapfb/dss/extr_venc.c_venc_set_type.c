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
struct omap_dss_device {int dummy; } ;
typedef  enum omap_dss_venc_type { ____Placeholder_omap_dss_venc_type } omap_dss_venc_type ;
struct TYPE_2__ {int type; int /*<<< orphan*/  venc_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__ venc ; 

__attribute__((used)) static void venc_set_type(struct omap_dss_device *dssdev,
		enum omap_dss_venc_type type)
{
	mutex_lock(&venc.venc_lock);

	venc.type = type;

	mutex_unlock(&venc.venc_lock);
}