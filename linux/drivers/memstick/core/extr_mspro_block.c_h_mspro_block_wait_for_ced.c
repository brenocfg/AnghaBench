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
struct memstick_request {int* data; int /*<<< orphan*/  error; } ;
struct memstick_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int MEMSTICK_INT_CED ; 
 int MEMSTICK_INT_CMDNAK ; 
 int MEMSTICK_INT_ERR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int mspro_block_complete_req (struct memstick_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int h_mspro_block_wait_for_ced(struct memstick_dev *card,
				      struct memstick_request **mrq)
{
	dev_dbg(&card->dev, "wait for ced: value %x\n", (*mrq)->data[0]);

	if (!(*mrq)->error) {
		if ((*mrq)->data[0] & (MEMSTICK_INT_CMDNAK | MEMSTICK_INT_ERR))
			(*mrq)->error = -EFAULT;
		else if (!((*mrq)->data[0] & MEMSTICK_INT_CED))
			return 0;
	}

	return mspro_block_complete_req(card, (*mrq)->error);
}