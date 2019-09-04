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
struct vpfe_device {int /*<<< orphan*/  lock; int /*<<< orphan*/  pdev; int /*<<< orphan*/  ccdc; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int _vb2_fop_release (struct file*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int v4l2_fh_is_singular_file (struct file*) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vpfe_ccdc_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vpfe_release(struct file *file)
{
	struct vpfe_device *vpfe = video_drvdata(file);
	bool fh_singular;
	int ret;

	mutex_lock(&vpfe->lock);

	/* Save the singular status before we call the clean-up helper */
	fh_singular = v4l2_fh_is_singular_file(file);

	/* the release helper will cleanup any on-going streaming */
	ret = _vb2_fop_release(file, NULL);

	/*
	 * If this was the last open file.
	 * Then de-initialize hw module.
	 */
	if (fh_singular)
		vpfe_ccdc_close(&vpfe->ccdc, vpfe->pdev);

	mutex_unlock(&vpfe->lock);

	return ret;
}