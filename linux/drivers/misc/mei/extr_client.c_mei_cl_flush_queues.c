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
struct mei_device {int /*<<< orphan*/  ctrl_rd_list; int /*<<< orphan*/  ctrl_wr_list; int /*<<< orphan*/  write_waiting_list; int /*<<< orphan*/  write_list; } ;
struct mei_cl {int /*<<< orphan*/  rd_completed; int /*<<< orphan*/  rd_pending; struct mei_device* dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  cl_dbg (struct mei_device*,struct mei_cl*,char*) ; 
 int /*<<< orphan*/  mei_io_list_flush_cl (int /*<<< orphan*/ *,struct mei_cl*) ; 
 int /*<<< orphan*/  mei_io_list_free_fp (int /*<<< orphan*/ *,struct file const*) ; 
 int /*<<< orphan*/  mei_io_tx_list_free_cl (int /*<<< orphan*/ *,struct mei_cl*) ; 

int mei_cl_flush_queues(struct mei_cl *cl, const struct file *fp)
{
	struct mei_device *dev;

	if (WARN_ON(!cl || !cl->dev))
		return -EINVAL;

	dev = cl->dev;

	cl_dbg(dev, cl, "remove list entry belonging to cl\n");
	mei_io_tx_list_free_cl(&cl->dev->write_list, cl);
	mei_io_tx_list_free_cl(&cl->dev->write_waiting_list, cl);
	mei_io_list_flush_cl(&cl->dev->ctrl_wr_list, cl);
	mei_io_list_flush_cl(&cl->dev->ctrl_rd_list, cl);
	mei_io_list_free_fp(&cl->rd_pending, fp);
	mei_io_list_free_fp(&cl->rd_completed, fp);

	return 0;
}