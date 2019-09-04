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
struct coresight_device {int dummy; } ;
struct catu_drvdata {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CS_UNLOCK (int /*<<< orphan*/ ) ; 
 int catu_disable_hw (struct catu_drvdata*) ; 
 struct catu_drvdata* csdev_to_catu_drvdata (struct coresight_device*) ; 

__attribute__((used)) static int catu_disable(struct coresight_device *csdev, void *__unused)
{
	int rc;
	struct catu_drvdata *catu_drvdata = csdev_to_catu_drvdata(csdev);

	CS_UNLOCK(catu_drvdata->base);
	rc = catu_disable_hw(catu_drvdata);
	CS_LOCK(catu_drvdata->base);
	return rc;
}