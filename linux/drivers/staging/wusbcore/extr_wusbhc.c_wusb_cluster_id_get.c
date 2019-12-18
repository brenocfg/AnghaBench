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
typedef  scalar_t__ u8 ;

/* Variables and functions */
 scalar_t__ CLUSTER_IDS ; 
 scalar_t__ find_first_zero_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wusb_cluster_id_table ; 
 int /*<<< orphan*/  wusb_cluster_ids_lock ; 

u8 wusb_cluster_id_get(void)
{
	u8 id;
	spin_lock(&wusb_cluster_ids_lock);
	id = find_first_zero_bit(wusb_cluster_id_table, CLUSTER_IDS);
	if (id >= CLUSTER_IDS) {
		id = 0;
		goto out;
	}
	set_bit(id, wusb_cluster_id_table);
	id = (u8) 0xff - id;
out:
	spin_unlock(&wusb_cluster_ids_lock);
	return id;

}