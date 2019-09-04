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
struct sirf_data {struct gnss_device* gdev; } ;
struct serdev_device {int dummy; } ;
struct gnss_device {int dummy; } ;

/* Variables and functions */
 int gnss_insert_raw (struct gnss_device*,unsigned char const*,size_t) ; 
 struct sirf_data* serdev_device_get_drvdata (struct serdev_device*) ; 

__attribute__((used)) static int sirf_receive_buf(struct serdev_device *serdev,
				const unsigned char *buf, size_t count)
{
	struct sirf_data *data = serdev_device_get_drvdata(serdev);
	struct gnss_device *gdev = data->gdev;

	return gnss_insert_raw(gdev, buf, count);
}