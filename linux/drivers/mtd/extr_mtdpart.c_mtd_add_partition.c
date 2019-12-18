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
struct mtd_partition {char const* name; long long size; long long offset; } ;
struct mtd_part {int /*<<< orphan*/  list; int /*<<< orphan*/  mtd; } ;
struct mtd_info {long long size; } ;
typedef  int /*<<< orphan*/  part ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct mtd_part*) ; 
 long long MTDPART_OFS_APPEND ; 
 long long MTDPART_OFS_NXTBLK ; 
 long long MTDPART_SIZ_FULL ; 
 int PTR_ERR (struct mtd_part*) ; 
 int add_mtd_device (int /*<<< orphan*/ *) ; 
 struct mtd_part* allocate_partition (struct mtd_info*,struct mtd_partition*,int,long long) ; 
 int /*<<< orphan*/  free_partition (struct mtd_part*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mtd_partition*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtd_add_partition_attrs (struct mtd_part*) ; 
 int /*<<< orphan*/  mtd_partitions ; 
 int /*<<< orphan*/  mtd_partitions_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mtd_add_partition(struct mtd_info *parent, const char *name,
		      long long offset, long long length)
{
	struct mtd_partition part;
	struct mtd_part *new;
	int ret = 0;

	/* the direct offset is expected */
	if (offset == MTDPART_OFS_APPEND ||
	    offset == MTDPART_OFS_NXTBLK)
		return -EINVAL;

	if (length == MTDPART_SIZ_FULL)
		length = parent->size - offset;

	if (length <= 0)
		return -EINVAL;

	memset(&part, 0, sizeof(part));
	part.name = name;
	part.size = length;
	part.offset = offset;

	new = allocate_partition(parent, &part, -1, offset);
	if (IS_ERR(new))
		return PTR_ERR(new);

	mutex_lock(&mtd_partitions_mutex);
	list_add(&new->list, &mtd_partitions);
	mutex_unlock(&mtd_partitions_mutex);

	ret = add_mtd_device(&new->mtd);
	if (ret)
		goto err_remove_part;

	mtd_add_partition_attrs(new);

	return 0;

err_remove_part:
	mutex_lock(&mtd_partitions_mutex);
	list_del(&new->list);
	mutex_unlock(&mtd_partitions_mutex);

	free_partition(new);

	return ret;
}