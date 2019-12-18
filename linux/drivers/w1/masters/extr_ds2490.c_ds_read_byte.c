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
typedef  int /*<<< orphan*/  u8 ;
struct ds_status {int dummy; } ;
struct ds_device {int dummy; } ;

/* Variables and functions */
 int COMM_BYTE_IO ; 
 int COMM_IM ; 
 int ds_recv_data (struct ds_device*,int /*<<< orphan*/ *,int) ; 
 int ds_send_control (struct ds_device*,int,int) ; 
 int /*<<< orphan*/  ds_wait_status (struct ds_device*,struct ds_status*) ; 

__attribute__((used)) static int ds_read_byte(struct ds_device *dev, u8 *byte)
{
	int err;
	struct ds_status st;

	err = ds_send_control(dev, COMM_BYTE_IO | COMM_IM, 0xff);
	if (err)
		return err;

	ds_wait_status(dev, &st);

	err = ds_recv_data(dev, byte, sizeof(*byte));
	if (err < 0)
		return err;

	return 0;
}