#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_6__ {TYPE_2__* input; } ;
struct TYPE_4__ {int product; } ;
struct TYPE_5__ {TYPE_1__ id; } ;

/* Variables and functions */
 TYPE_3__** adbhid ; 
 int /*<<< orphan*/  adbhid_input_register (int,int,int,int,int) ; 
 int /*<<< orphan*/  adbhid_input_unregister (int) ; 

__attribute__((used)) static u16
adbhid_input_reregister(int id, int default_id, int org_handler_id,
			int cur_handler_id, int mk)
{
	if (adbhid[id]) {
		if (adbhid[id]->input->id.product !=
		    ((id << 12)|(default_id << 8)|org_handler_id)) {
			adbhid_input_unregister(id);
			adbhid_input_register(id, default_id, org_handler_id,
					      cur_handler_id, mk);
		}
	} else
		adbhid_input_register(id, default_id, org_handler_id,
				      cur_handler_id, mk);
	return 1<<id;
}