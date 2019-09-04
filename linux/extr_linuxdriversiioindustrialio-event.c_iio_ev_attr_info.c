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
struct iio_dev_attr {int address; } ;
typedef  enum iio_event_info { ____Placeholder_iio_event_info } iio_event_info ;

/* Variables and functions */

__attribute__((used)) static enum iio_event_info iio_ev_attr_info(struct iio_dev_attr *attr)
{
	return (attr->address >> 16) & 0xffff;
}