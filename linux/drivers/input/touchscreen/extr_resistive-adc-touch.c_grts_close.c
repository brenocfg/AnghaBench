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
struct input_dev {int dummy; } ;
struct grts_state {int /*<<< orphan*/  iio_cb; } ;

/* Variables and functions */
 int /*<<< orphan*/  iio_channel_stop_all_cb (int /*<<< orphan*/ ) ; 
 struct grts_state* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static void grts_close(struct input_dev *dev)
{
	struct grts_state *st = input_get_drvdata(dev);

	iio_channel_stop_all_cb(st->iio_cb);
}