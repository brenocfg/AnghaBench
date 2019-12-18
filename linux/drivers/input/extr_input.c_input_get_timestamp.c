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
struct input_dev {int /*<<< orphan*/ * timestamp; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 size_t INPUT_CLK_MONO ; 
 int /*<<< orphan*/  input_set_timestamp (struct input_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_compare (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ktime_t *input_get_timestamp(struct input_dev *dev)
{
	const ktime_t invalid_timestamp = ktime_set(0, 0);

	if (!ktime_compare(dev->timestamp[INPUT_CLK_MONO], invalid_timestamp))
		input_set_timestamp(dev, ktime_get());

	return dev->timestamp;
}