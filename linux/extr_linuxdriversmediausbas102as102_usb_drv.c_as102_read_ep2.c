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
struct as10x_bus_adapter_t {TYPE_1__* usb_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 
 int usb_bulk_msg (TYPE_1__*,int /*<<< orphan*/ ,unsigned char*,int,int*,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (TYPE_1__*,int) ; 

__attribute__((used)) static int as102_read_ep2(struct as10x_bus_adapter_t *bus_adap,
		   unsigned char *recv_buf, int recv_buf_len)
{
	int ret, actual_len;

	if (recv_buf == NULL)
		return -EINVAL;

	ret = usb_bulk_msg(bus_adap->usb_dev,
			   usb_rcvbulkpipe(bus_adap->usb_dev, 2),
			   recv_buf, recv_buf_len, &actual_len, 200);
	if (ret) {
		dev_dbg(&bus_adap->usb_dev->dev,
			"usb_bulk_msg(recv) failed, err %i\n", ret);
		return ret;
	}

	if (actual_len != recv_buf_len) {
		dev_dbg(&bus_adap->usb_dev->dev, "only read %d of %d bytes\n",
			actual_len, recv_buf_len);
		return -1;
	}
	return actual_len;
}