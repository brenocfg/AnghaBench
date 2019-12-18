#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  client; } ;
struct log_c {TYPE_1__ io_req; int /*<<< orphan*/  disk_header; int /*<<< orphan*/  log_dev; int /*<<< orphan*/  ti; } ;
struct dm_dirty_log {scalar_t__ context; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy_log_context (struct log_c*) ; 
 int /*<<< orphan*/  dm_io_client_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_put_device (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disk_dtr(struct dm_dirty_log *log)
{
	struct log_c *lc = (struct log_c *) log->context;

	dm_put_device(lc->ti, lc->log_dev);
	vfree(lc->disk_header);
	dm_io_client_destroy(lc->io_req.client);
	destroy_log_context(lc);
}