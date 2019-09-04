#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct iio_dev_attr {int address; TYPE_2__* c; } ;
typedef  enum iio_event_direction { ____Placeholder_iio_event_direction } iio_event_direction ;
struct TYPE_4__ {TYPE_1__* event_spec; } ;
struct TYPE_3__ {int dir; } ;

/* Variables and functions */

__attribute__((used)) static enum iio_event_direction iio_ev_attr_dir(struct iio_dev_attr *attr)
{
	return attr->c->event_spec[attr->address & 0xffff].dir;
}