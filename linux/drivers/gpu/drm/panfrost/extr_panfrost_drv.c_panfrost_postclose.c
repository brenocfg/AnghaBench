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
struct panfrost_file_priv {int /*<<< orphan*/  mm; } ;
struct drm_file {struct panfrost_file_priv* driver_priv; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_mm_takedown (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct panfrost_file_priv*) ; 
 int /*<<< orphan*/  panfrost_job_close (struct panfrost_file_priv*) ; 
 int /*<<< orphan*/  panfrost_mmu_pgtable_free (struct panfrost_file_priv*) ; 
 int /*<<< orphan*/  panfrost_perfcnt_close (struct panfrost_file_priv*) ; 

__attribute__((used)) static void
panfrost_postclose(struct drm_device *dev, struct drm_file *file)
{
	struct panfrost_file_priv *panfrost_priv = file->driver_priv;

	panfrost_perfcnt_close(panfrost_priv);
	panfrost_job_close(panfrost_priv);

	panfrost_mmu_pgtable_free(panfrost_priv);
	drm_mm_takedown(&panfrost_priv->mm);
	kfree(panfrost_priv);
}