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
struct hts221_hw {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int devm_iio_triggered_buffer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hts221_buffer_handler_thread ; 
 int /*<<< orphan*/  hts221_buffer_ops ; 
 int /*<<< orphan*/  iio_priv_to_dev (struct hts221_hw*) ; 

int hts221_allocate_buffers(struct hts221_hw *hw)
{
	return devm_iio_triggered_buffer_setup(hw->dev, iio_priv_to_dev(hw),
					NULL, hts221_buffer_handler_thread,
					&hts221_buffer_ops);
}