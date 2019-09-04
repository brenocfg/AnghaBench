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
struct mei_device {int dummy; } ;
struct mei_cl {struct mei_device* dev; int /*<<< orphan*/  state; int /*<<< orphan*/  writing_state; int /*<<< orphan*/  link; int /*<<< orphan*/  rd_pending; int /*<<< orphan*/  rd_completed; int /*<<< orphan*/  ev_wait; int /*<<< orphan*/  tx_wait; int /*<<< orphan*/  rx_wait; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MEI_FILE_UNINITIALIZED ; 
 int /*<<< orphan*/  MEI_IDLE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct mei_cl*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void mei_cl_init(struct mei_cl *cl, struct mei_device *dev)
{
	memset(cl, 0, sizeof(struct mei_cl));
	init_waitqueue_head(&cl->wait);
	init_waitqueue_head(&cl->rx_wait);
	init_waitqueue_head(&cl->tx_wait);
	init_waitqueue_head(&cl->ev_wait);
	INIT_LIST_HEAD(&cl->rd_completed);
	INIT_LIST_HEAD(&cl->rd_pending);
	INIT_LIST_HEAD(&cl->link);
	cl->writing_state = MEI_IDLE;
	cl->state = MEI_FILE_UNINITIALIZED;
	cl->dev = dev;
}