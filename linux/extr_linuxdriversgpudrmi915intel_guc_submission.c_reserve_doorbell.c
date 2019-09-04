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
typedef  unsigned long u16 ;
struct intel_guc_client {unsigned long doorbell_id; int /*<<< orphan*/  stage_id; TYPE_1__* guc; } ;
struct TYPE_2__ {int /*<<< orphan*/  doorbell_bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 unsigned long GUC_DOORBELL_INVALID ; 
 int GUC_NUM_DOORBELLS ; 
 int /*<<< orphan*/  __set_bit (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long find_next_zero_bit (int /*<<< orphan*/ ,unsigned long,unsigned long) ; 
 scalar_t__ is_high_priority (struct intel_guc_client*) ; 
 int /*<<< orphan*/  yesno (scalar_t__) ; 

__attribute__((used)) static int reserve_doorbell(struct intel_guc_client *client)
{
	unsigned long offset;
	unsigned long end;
	u16 id;

	GEM_BUG_ON(client->doorbell_id != GUC_DOORBELL_INVALID);

	/*
	 * The bitmap tracks which doorbell registers are currently in use.
	 * It is split into two halves; the first half is used for normal
	 * priority contexts, the second half for high-priority ones.
	 */
	offset = 0;
	end = GUC_NUM_DOORBELLS / 2;
	if (is_high_priority(client)) {
		offset = end;
		end += offset;
	}

	id = find_next_zero_bit(client->guc->doorbell_bitmap, end, offset);
	if (id == end)
		return -ENOSPC;

	__set_bit(id, client->guc->doorbell_bitmap);
	client->doorbell_id = id;
	DRM_DEBUG_DRIVER("client %u (high prio=%s) reserved doorbell: %d\n",
			 client->stage_id, yesno(is_high_priority(client)),
			 id);
	return 0;
}