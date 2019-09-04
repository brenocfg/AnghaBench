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
typedef  scalar_t__ uint64_t ;
struct mtd_info {scalar_t__ size; scalar_t__ erasesize; struct docg3* priv; } ;
struct erase_info {scalar_t__ addr; scalar_t__ len; } ;
struct docg3 {TYPE_1__* cascade; int /*<<< orphan*/  device_id; int /*<<< orphan*/  reliable; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  calc_block_sector (scalar_t__,int*,int*,int*,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_dbg (char*,scalar_t__,scalar_t__) ; 
 int doc_erase_block (struct docg3*,int,int) ; 
 int /*<<< orphan*/  doc_set_device_id (struct docg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  doc_set_reliable_mode (struct docg3*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int doc_erase(struct mtd_info *mtd, struct erase_info *info)
{
	struct docg3 *docg3 = mtd->priv;
	uint64_t len;
	int block0, block1, page, ret = 0, ofs = 0;

	doc_dbg("doc_erase(from=%lld, len=%lld\n", info->addr, info->len);

	calc_block_sector(info->addr + info->len, &block0, &block1, &page,
			  &ofs, docg3->reliable);
	if (info->addr + info->len > mtd->size || page || ofs)
		return -EINVAL;

	calc_block_sector(info->addr, &block0, &block1, &page, &ofs,
			  docg3->reliable);
	mutex_lock(&docg3->cascade->lock);
	doc_set_device_id(docg3, docg3->device_id);
	doc_set_reliable_mode(docg3);
	for (len = info->len; !ret && len > 0; len -= mtd->erasesize) {
		ret = doc_erase_block(docg3, block0, block1);
		block0 += 2;
		block1 += 2;
	}
	mutex_unlock(&docg3->cascade->lock);

	return ret;
}