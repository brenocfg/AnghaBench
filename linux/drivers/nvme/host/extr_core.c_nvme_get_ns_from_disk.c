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
struct nvme_ns_head {int /*<<< orphan*/  srcu; } ;
struct nvme_ns {int /*<<< orphan*/  srcu; } ;
struct gendisk {struct nvme_ns_head* private_data; int /*<<< orphan*/ * fops; } ;

/* Variables and functions */
 struct nvme_ns_head* nvme_find_path (struct nvme_ns_head*) ; 
 int /*<<< orphan*/  nvme_ns_head_ops ; 
 int srcu_read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_read_unlock (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct nvme_ns *nvme_get_ns_from_disk(struct gendisk *disk,
		struct nvme_ns_head **head, int *srcu_idx)
{
#ifdef CONFIG_NVME_MULTIPATH
	if (disk->fops == &nvme_ns_head_ops) {
		struct nvme_ns *ns;

		*head = disk->private_data;
		*srcu_idx = srcu_read_lock(&(*head)->srcu);
		ns = nvme_find_path(*head);
		if (!ns)
			srcu_read_unlock(&(*head)->srcu, *srcu_idx);
		return ns;
	}
#endif
	*head = NULL;
	*srcu_idx = -1;
	return disk->private_data;
}