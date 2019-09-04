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
struct gp2ap020a00f_data {int /*<<< orphan*/  flags; int /*<<< orphan*/  data_ready_queue; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  GP2AP020A00F_DATA_READY_TIMEOUT ; 
 int /*<<< orphan*/  GP2AP020A00F_FLAG_DATA_READY ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wait_conversion_complete_irq(struct gp2ap020a00f_data *data)
{
	int ret;

	ret = wait_event_timeout(data->data_ready_queue,
				 test_bit(GP2AP020A00F_FLAG_DATA_READY,
					  &data->flags),
				 GP2AP020A00F_DATA_READY_TIMEOUT);
	clear_bit(GP2AP020A00F_FLAG_DATA_READY, &data->flags);

	return ret > 0 ? 0 : -ETIME;
}