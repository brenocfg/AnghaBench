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
struct ls_scfg_msi {int msir_num; int /*<<< orphan*/  parent; int /*<<< orphan*/  msi_domain; int /*<<< orphan*/ * msir; } ;

/* Variables and functions */
 int /*<<< orphan*/  irq_domain_remove (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ls_scfg_msi_teardown_hwirq (int /*<<< orphan*/ *) ; 
 struct ls_scfg_msi* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ls_scfg_msi_remove(struct platform_device *pdev)
{
	struct ls_scfg_msi *msi_data = platform_get_drvdata(pdev);
	int i;

	for (i = 0; i < msi_data->msir_num; i++)
		ls_scfg_msi_teardown_hwirq(&msi_data->msir[i]);

	irq_domain_remove(msi_data->msi_domain);
	irq_domain_remove(msi_data->parent);

	platform_set_drvdata(pdev, NULL);

	return 0;
}