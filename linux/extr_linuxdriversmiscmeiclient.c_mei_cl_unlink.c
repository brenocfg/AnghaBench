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
struct mei_device {scalar_t__ open_handle_count; int /*<<< orphan*/  host_clients_map; } ;
struct mei_cl {int /*<<< orphan*/  link; int /*<<< orphan*/  rd_pending; int /*<<< orphan*/  rd_completed; int /*<<< orphan*/  writing_state; int /*<<< orphan*/  state; scalar_t__ host_client_id; struct mei_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEI_FILE_UNINITIALIZED ; 
 int /*<<< orphan*/  MEI_IDLE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

int mei_cl_unlink(struct mei_cl *cl)
{
	struct mei_device *dev;

	/* don't shout on error exit path */
	if (!cl)
		return 0;

	if (WARN_ON(!cl->dev))
		return 0;

	dev = cl->dev;

	cl_dbg(dev, cl, "unlink client");

	if (dev->open_handle_count > 0)
		dev->open_handle_count--;

	/* never clear the 0 bit */
	if (cl->host_client_id)
		clear_bit(cl->host_client_id, dev->host_clients_map);

	list_del_init(&cl->link);

	cl->state = MEI_FILE_UNINITIALIZED;
	cl->writing_state = MEI_IDLE;

	WARN_ON(!list_empty(&cl->rd_completed) ||
		!list_empty(&cl->rd_pending) ||
		!list_empty(&cl->link));

	return 0;
}