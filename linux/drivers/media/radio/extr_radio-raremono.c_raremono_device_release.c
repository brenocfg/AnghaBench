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
struct v4l2_device {int dummy; } ;
struct raremono_device {struct raremono_device* buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct raremono_device*) ; 
 struct raremono_device* to_raremono_dev (struct v4l2_device*) ; 

__attribute__((used)) static void raremono_device_release(struct v4l2_device *v4l2_dev)
{
	struct raremono_device *radio = to_raremono_dev(v4l2_dev);

	kfree(radio->buffer);
	kfree(radio);
}