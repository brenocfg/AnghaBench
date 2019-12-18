#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct smu_sdbp_header {int len; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTK (char*,...) ; 
 struct smu_sdbp_header const* ERR_PTR (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct smu_sdbp_header* of_get_property (int /*<<< orphan*/ ,char*,unsigned int*) ; 
 TYPE_1__* smu ; 
 struct smu_sdbp_header* smu_create_sdb_partition (int) ; 
 int /*<<< orphan*/  smu_part_access ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const struct smu_sdbp_header *__smu_get_sdb_partition(int id,
		unsigned int *size, int interruptible)
{
	char pname[32];
	const struct smu_sdbp_header *part;

	if (!smu)
		return NULL;

	sprintf(pname, "sdb-partition-%02x", id);

	DPRINTK("smu_get_sdb_partition(%02x)\n", id);

	if (interruptible) {
		int rc;
		rc = mutex_lock_interruptible(&smu_part_access);
		if (rc)
			return ERR_PTR(rc);
	} else
		mutex_lock(&smu_part_access);

	part = of_get_property(smu->of_node, pname, size);
	if (part == NULL) {
		DPRINTK("trying to extract from SMU ...\n");
		part = smu_create_sdb_partition(id);
		if (part != NULL && size)
			*size = part->len << 2;
	}
	mutex_unlock(&smu_part_access);
	return part;
}