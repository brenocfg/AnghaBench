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
struct platform_device {int dummy; } ;
struct camss {unsigned int vfe_num; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  notifier; int /*<<< orphan*/ * vfe; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  camss_delete (struct camss*) ; 
 int /*<<< orphan*/  camss_unregister_entities (struct camss*) ; 
 int /*<<< orphan*/  msm_vfe_stop_streaming (int /*<<< orphan*/ *) ; 
 struct camss* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_async_notifier_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_async_notifier_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int camss_remove(struct platform_device *pdev)
{
	unsigned int i;

	struct camss *camss = platform_get_drvdata(pdev);

	for (i = 0; i < camss->vfe_num; i++)
		msm_vfe_stop_streaming(&camss->vfe[i]);

	v4l2_async_notifier_unregister(&camss->notifier);
	v4l2_async_notifier_cleanup(&camss->notifier);
	camss_unregister_entities(camss);

	if (atomic_read(&camss->ref_count) == 0)
		camss_delete(camss);

	return 0;
}