#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct knav_queue_inst {int dummy; } ;
struct TYPE_3__ {int base_id; int num_queues; } ;

/* Variables and functions */
 TYPE_1__* kdev ; 
 struct knav_queue_inst* knav_queue_match_id_to_inst (TYPE_1__*,int) ; 

__attribute__((used)) static inline struct knav_queue_inst *knav_queue_find_by_id(int id)
{
	if (kdev->base_id <= id &&
	    kdev->base_id + kdev->num_queues > id) {
		id -= kdev->base_id;
		return knav_queue_match_id_to_inst(kdev, id);
	}
	return NULL;
}