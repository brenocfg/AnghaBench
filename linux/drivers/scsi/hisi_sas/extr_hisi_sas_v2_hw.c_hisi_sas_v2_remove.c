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
struct sas_ha_struct {struct hisi_hba* lldd_ha; } ;
struct platform_device {int dummy; } ;
struct hisi_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_sas_kill_tasklets (struct hisi_hba*) ; 
 int hisi_sas_remove (struct platform_device*) ; 
 struct sas_ha_struct* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int hisi_sas_v2_remove(struct platform_device *pdev)
{
	struct sas_ha_struct *sha = platform_get_drvdata(pdev);
	struct hisi_hba *hisi_hba = sha->lldd_ha;

	hisi_sas_kill_tasklets(hisi_hba);

	return hisi_sas_remove(pdev);
}