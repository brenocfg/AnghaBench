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
typedef  int u16 ;
typedef  enum usnic_transport_type { ____Placeholder_usnic_transport_type } usnic_transport_type ;

/* Variables and functions */
 int /*<<< orphan*/  ROCE_BITMAP_SZ ; 
 int USNIC_TRANSPORT_ROCE_CUSTOM ; 
 int bitmap_find_next_zero_area (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  roce_bitmap ; 
 int /*<<< orphan*/  roce_bitmap_lock ; 
 int roce_next_port ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_dbg (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usnic_transport_to_str (int) ; 

u16 usnic_transport_rsrv_port(enum usnic_transport_type type, u16 port_num)
{
	if (type == USNIC_TRANSPORT_ROCE_CUSTOM) {
		spin_lock(&roce_bitmap_lock);
		if (!port_num) {
			port_num = bitmap_find_next_zero_area(roce_bitmap,
						ROCE_BITMAP_SZ,
						roce_next_port /* start */,
						1 /* nr */,
						0 /* align */);
			roce_next_port = (port_num & 4095) + 1;
		} else if (test_bit(port_num, roce_bitmap)) {
			usnic_err("Failed to allocate port for %s\n",
					usnic_transport_to_str(type));
			spin_unlock(&roce_bitmap_lock);
			goto out_fail;
		}
		bitmap_set(roce_bitmap, port_num, 1);
		spin_unlock(&roce_bitmap_lock);
	} else {
		usnic_err("Failed to allocate port - transport %s unsupported\n",
				usnic_transport_to_str(type));
		goto out_fail;
	}

	usnic_dbg("Allocating port %hu for %s\n", port_num,
			usnic_transport_to_str(type));
	return port_num;

out_fail:
	return 0;
}