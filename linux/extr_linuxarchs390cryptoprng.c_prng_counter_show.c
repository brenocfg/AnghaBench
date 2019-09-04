#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_5__ {int /*<<< orphan*/  byte_counter; } ;
struct TYPE_4__ {int /*<<< orphan*/  stream_bytes; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; TYPE_2__ prngws; TYPE_1__ prnows; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERESTARTSYS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PRNG_MODE_SHA512 ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_3__* prng_data ; 
 scalar_t__ prng_mode ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t prng_counter_show(struct device *dev,
				 struct device_attribute *attr,
				 char *buf)
{
	u64 counter;

	if (mutex_lock_interruptible(&prng_data->mutex))
		return -ERESTARTSYS;
	if (prng_mode == PRNG_MODE_SHA512)
		counter = prng_data->prnows.stream_bytes;
	else
		counter = prng_data->prngws.byte_counter;
	mutex_unlock(&prng_data->mutex);

	return snprintf(buf, PAGE_SIZE, "%llu\n", counter);
}