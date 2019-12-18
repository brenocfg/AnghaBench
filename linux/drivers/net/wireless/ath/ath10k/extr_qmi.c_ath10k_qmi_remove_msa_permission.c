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
struct ath10k_qmi {int nr_mem_region; int /*<<< orphan*/ * mem_region; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_qmi_unmap_msa_permission (struct ath10k_qmi*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_qmi_remove_msa_permission(struct ath10k_qmi *qmi)
{
	int i;

	for (i = 0; i < qmi->nr_mem_region; i++)
		ath10k_qmi_unmap_msa_permission(qmi, &qmi->mem_region[i]);
}