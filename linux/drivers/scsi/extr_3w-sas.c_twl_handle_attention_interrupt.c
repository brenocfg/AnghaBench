#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_9__ {int /*<<< orphan*/  flags; int /*<<< orphan*/ * state; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ TW_Device_Extension ;

/* Variables and functions */
 int /*<<< orphan*/  TWL_CLEAR_DB_INTERRUPT (TYPE_1__*) ; 
 int TWL_DOORBELL_ATTENTION_INTERRUPT ; 
 int TWL_DOORBELL_CONTROLLER_ERROR ; 
 int /*<<< orphan*/  TWL_HOBDBC_REG_ADDR (TYPE_1__*) ; 
 int /*<<< orphan*/  TWL_HOBDB_REG_ADDR (TYPE_1__*) ; 
 int /*<<< orphan*/  TW_DRIVER ; 
 int /*<<< orphan*/  TW_IN_ATTENTION_LOOP ; 
 int /*<<< orphan*/  TW_PRINTK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  TW_S_COMPLETED ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ twl_aen_read_queue (TYPE_1__*,int) ; 
 int /*<<< orphan*/  twl_free_request_id (TYPE_1__*,int) ; 
 int /*<<< orphan*/  twl_get_request_id (TYPE_1__*,int*) ; 

__attribute__((used)) static int twl_handle_attention_interrupt(TW_Device_Extension *tw_dev)
{
	int retval = 1;
	u32 request_id, doorbell;

	/* Read doorbell status */
	doorbell = readl(TWL_HOBDB_REG_ADDR(tw_dev));

	/* Check for controller errors */
	if (doorbell & TWL_DOORBELL_CONTROLLER_ERROR) {
		TW_PRINTK(tw_dev->host, TW_DRIVER, 0xd, "Microcontroller Error: clearing");
		goto out;
	}

	/* Check if we need to perform an AEN drain */
	if (doorbell & TWL_DOORBELL_ATTENTION_INTERRUPT) {
		if (!(test_and_set_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags))) {
			twl_get_request_id(tw_dev, &request_id);
			if (twl_aen_read_queue(tw_dev, request_id)) {
				tw_dev->state[request_id] = TW_S_COMPLETED;
				twl_free_request_id(tw_dev, request_id);
				clear_bit(TW_IN_ATTENTION_LOOP, &tw_dev->flags);
			}
		}
	}

	retval = 0;
out:
	/* Clear doorbell interrupt */
	TWL_CLEAR_DB_INTERRUPT(tw_dev);

	/* Make sure the clear was flushed by reading it back */
	readl(TWL_HOBDBC_REG_ADDR(tw_dev));

	return retval;
}