#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct smcd_event {int dummy; } ;
struct ism_dev {int ieq_idx; int /*<<< orphan*/  smcd; TYPE_2__* ieq; } ;
struct TYPE_3__ {int /*<<< orphan*/  idx; } ;
struct TYPE_4__ {struct smcd_event* entry; TYPE_1__ header; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (struct smcd_event*) ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_event (int /*<<< orphan*/ ,int,struct smcd_event*,int) ; 
 int /*<<< orphan*/  ism_debug_info ; 
 int /*<<< orphan*/  smcd_handle_event (int /*<<< orphan*/ ,struct smcd_event*) ; 

__attribute__((used)) static void ism_handle_event(struct ism_dev *ism)
{
	struct smcd_event *entry;

	while ((ism->ieq_idx + 1) != READ_ONCE(ism->ieq->header.idx)) {
		if (++(ism->ieq_idx) == ARRAY_SIZE(ism->ieq->entry))
			ism->ieq_idx = 0;

		entry = &ism->ieq->entry[ism->ieq_idx];
		debug_event(ism_debug_info, 2, entry, sizeof(*entry));
		smcd_handle_event(ism->smcd, entry);
	}
}