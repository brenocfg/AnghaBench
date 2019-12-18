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
struct ptp_qoriq {int /*<<< orphan*/  rsrc; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ptp_qoriq*) ; 
 struct ptp_qoriq* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  ptp_qoriq_free (struct ptp_qoriq*) ; 
 int /*<<< orphan*/  release_resource (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ptp_qoriq_remove(struct platform_device *dev)
{
	struct ptp_qoriq *ptp_qoriq = platform_get_drvdata(dev);

	ptp_qoriq_free(ptp_qoriq);
	release_resource(ptp_qoriq->rsrc);
	kfree(ptp_qoriq);
	return 0;
}