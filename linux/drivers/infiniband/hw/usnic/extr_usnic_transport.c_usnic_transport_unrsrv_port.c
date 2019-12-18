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
typedef  int /*<<< orphan*/  u16 ;
typedef  enum usnic_transport_type { ____Placeholder_usnic_transport_type } usnic_transport_type ;

/* Variables and functions */
 int USNIC_TRANSPORT_ROCE_CUSTOM ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  roce_bitmap ; 
 int /*<<< orphan*/  roce_bitmap_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_dbg (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usnic_err (char*,int,...) ; 
 int usnic_transport_to_str (int) ; 

void usnic_transport_unrsrv_port(enum usnic_transport_type type, u16 port_num)
{
	if (type == USNIC_TRANSPORT_ROCE_CUSTOM) {
		spin_lock(&roce_bitmap_lock);
		if (!port_num) {
			usnic_err("Unreserved invalid port num 0 for %s\n",
					usnic_transport_to_str(type));
			goto out_roce_custom;
		}

		if (!test_bit(port_num, roce_bitmap)) {
			usnic_err("Unreserving invalid %hu for %s\n",
					port_num,
					usnic_transport_to_str(type));
			goto out_roce_custom;
		}
		bitmap_clear(roce_bitmap, port_num, 1);
		usnic_dbg("Freeing port %hu for %s\n", port_num,
				usnic_transport_to_str(type));
out_roce_custom:
		spin_unlock(&roce_bitmap_lock);
	} else {
		usnic_err("Freeing invalid port %hu for %d\n", port_num, type);
	}
}