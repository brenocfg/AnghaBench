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
typedef  unsigned int u32 ;
struct pm8001_hba_info {unsigned int tags_num; int /*<<< orphan*/  bitmap_lock; void* tags; } ;

/* Variables and functions */
 int SAS_QUEUE_FULL ; 
 unsigned int find_first_zero_bit (void*,unsigned int) ; 
 int /*<<< orphan*/  set_bit (unsigned int,void*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

inline int pm8001_tag_alloc(struct pm8001_hba_info *pm8001_ha, u32 *tag_out)
{
	unsigned int tag;
	void *bitmap = pm8001_ha->tags;
	unsigned long flags;

	spin_lock_irqsave(&pm8001_ha->bitmap_lock, flags);
	tag = find_first_zero_bit(bitmap, pm8001_ha->tags_num);
	if (tag >= pm8001_ha->tags_num) {
		spin_unlock_irqrestore(&pm8001_ha->bitmap_lock, flags);
		return -SAS_QUEUE_FULL;
	}
	set_bit(tag, bitmap);
	spin_unlock_irqrestore(&pm8001_ha->bitmap_lock, flags);
	*tag_out = tag;
	return 0;
}