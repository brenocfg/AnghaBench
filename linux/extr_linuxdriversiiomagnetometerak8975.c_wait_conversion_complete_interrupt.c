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
struct ak8975_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  data_ready_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  AK8975_DATA_READY_TIMEOUT ; 
 int ETIME ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_conversion_complete_interrupt(struct ak8975_data *data)
{
	int ret;

	ret = wait_event_timeout(data->data_ready_queue,
				 test_bit(0, &data->flags),
				 AK8975_DATA_READY_TIMEOUT);
	clear_bit(0, &data->flags);

	return ret > 0 ? 0 : -ETIME;
}