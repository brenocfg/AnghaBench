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
struct ds_device {int /*<<< orphan*/  byte_buf; } ;

/* Variables and functions */
 int ds_read_byte (struct ds_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 ds9490r_read_byte(void *data)
{
	struct ds_device *dev = data;
	int err;

	err = ds_read_byte(dev, &dev->byte_buf);
	if (err)
		return 0;

	return dev->byte_buf;
}