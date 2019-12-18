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
struct sis_file_private {int dummy; } ;
struct drm_file {struct sis_file_private* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct sis_file_private*) ; 

__attribute__((used)) static void sis_driver_postclose(struct drm_device *dev, struct drm_file *file)
{
	struct sis_file_private *file_priv = file->driver_priv;

	kfree(file_priv);
}