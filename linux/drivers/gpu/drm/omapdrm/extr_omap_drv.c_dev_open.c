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
struct drm_file {int /*<<< orphan*/ * driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,struct drm_device*,struct drm_file*) ; 

__attribute__((used)) static int dev_open(struct drm_device *dev, struct drm_file *file)
{
	file->driver_priv = NULL;

	DBG("open: dev=%p, file=%p", dev, file);

	return 0;
}