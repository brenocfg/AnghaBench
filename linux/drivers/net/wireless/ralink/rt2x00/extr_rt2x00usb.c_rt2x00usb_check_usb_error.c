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
struct rt2x00_dev {int num_proto_errs; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int EPROTO ; 
 int ETIMEDOUT ; 

__attribute__((used)) static bool rt2x00usb_check_usb_error(struct rt2x00_dev *rt2x00dev, int status)
{
	if (status == -ENODEV || status == -ENOENT)
		return true;

	if (status == -EPROTO || status == -ETIMEDOUT)
		rt2x00dev->num_proto_errs++;
	else
		rt2x00dev->num_proto_errs = 0;

	if (rt2x00dev->num_proto_errs > 3)
		return true;

	return false;
}