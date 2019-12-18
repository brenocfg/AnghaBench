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
struct msix_entry {int dummy; } ;
struct mic_irq_info {int num_vectors; struct msix_entry* msix_entries; int /*<<< orphan*/ * mic_msi_map; } ;
struct mic_device {struct mic_irq_info irq_info; } ;

/* Variables and functions */

__attribute__((used)) static struct msix_entry *mic_get_available_vector(struct mic_device *mdev)
{
	int i;
	struct mic_irq_info *info = &mdev->irq_info;

	for (i = 0; i < info->num_vectors; i++)
		if (!info->mic_msi_map[i])
			return &info->msix_entries[i];
	return NULL;
}