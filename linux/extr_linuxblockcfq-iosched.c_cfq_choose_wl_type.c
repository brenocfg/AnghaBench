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
typedef  scalar_t__ u64 ;
struct cfq_queue {scalar_t__ rb_key; } ;
struct cfq_group {int dummy; } ;
struct cfq_data {int dummy; } ;
typedef  enum wl_type_t { ____Placeholder_wl_type_t } wl_type_t ;
typedef  enum wl_class_t { ____Placeholder_wl_class_t } wl_class_t ;

/* Variables and functions */
 int SYNC_NOIDLE_WORKLOAD ; 
 int SYNC_WORKLOAD ; 
 struct cfq_queue* cfq_rb_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  st_for (struct cfq_group*,int,int) ; 

__attribute__((used)) static enum wl_type_t cfq_choose_wl_type(struct cfq_data *cfqd,
			struct cfq_group *cfqg, enum wl_class_t wl_class)
{
	struct cfq_queue *queue;
	int i;
	bool key_valid = false;
	u64 lowest_key = 0;
	enum wl_type_t cur_best = SYNC_NOIDLE_WORKLOAD;

	for (i = 0; i <= SYNC_WORKLOAD; ++i) {
		/* select the one with lowest rb_key */
		queue = cfq_rb_first(st_for(cfqg, wl_class, i));
		if (queue &&
		    (!key_valid || queue->rb_key < lowest_key)) {
			lowest_key = queue->rb_key;
			cur_best = i;
			key_valid = true;
		}
	}

	return cur_best;
}