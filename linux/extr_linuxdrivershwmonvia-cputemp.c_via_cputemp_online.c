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
struct pdev_entry {unsigned int cpu; int /*<<< orphan*/  list; struct platform_device* pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRVNAME ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct pdev_entry*) ; 
 struct pdev_entry* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pdev_list ; 
 int /*<<< orphan*/  pdev_list_mutex ; 
 int platform_device_add (struct platform_device*) ; 
 struct platform_device* platform_device_alloc (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  platform_device_put (struct platform_device*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int via_cputemp_online(unsigned int cpu)
{
	int err;
	struct platform_device *pdev;
	struct pdev_entry *pdev_entry;

	pdev = platform_device_alloc(DRVNAME, cpu);
	if (!pdev) {
		err = -ENOMEM;
		pr_err("Device allocation failed\n");
		goto exit;
	}

	pdev_entry = kzalloc(sizeof(struct pdev_entry), GFP_KERNEL);
	if (!pdev_entry) {
		err = -ENOMEM;
		goto exit_device_put;
	}

	err = platform_device_add(pdev);
	if (err) {
		pr_err("Device addition failed (%d)\n", err);
		goto exit_device_free;
	}

	pdev_entry->pdev = pdev;
	pdev_entry->cpu = cpu;
	mutex_lock(&pdev_list_mutex);
	list_add_tail(&pdev_entry->list, &pdev_list);
	mutex_unlock(&pdev_list_mutex);

	return 0;

exit_device_free:
	kfree(pdev_entry);
exit_device_put:
	platform_device_put(pdev);
exit:
	return err;
}