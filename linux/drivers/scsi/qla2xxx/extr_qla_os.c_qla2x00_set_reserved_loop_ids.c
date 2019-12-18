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
struct qla_hw_data {int /*<<< orphan*/  loop_id_map; } ;

/* Variables and functions */
 int BROADCAST ; 
 scalar_t__ IS_FWI2_CAPABLE (struct qla_hw_data*) ; 
 int MANAGEMENT_SERVER ; 
 int SNS_FIRST_LOOP_ID ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qla2x00_set_reserved_loop_ids(struct qla_hw_data *ha)
{
	int i;

	if (IS_FWI2_CAPABLE(ha))
		return;

	for (i = 0; i < SNS_FIRST_LOOP_ID; i++)
		set_bit(i, ha->loop_id_map);
	set_bit(MANAGEMENT_SERVER, ha->loop_id_map);
	set_bit(BROADCAST, ha->loop_id_map);
}