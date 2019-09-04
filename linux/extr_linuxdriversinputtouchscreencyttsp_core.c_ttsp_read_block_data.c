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
typedef  int /*<<< orphan*/  u8 ;
struct cyttsp {int /*<<< orphan*/  xfer_buf; int /*<<< orphan*/  dev; TYPE_1__* bus_ops; } ;
struct TYPE_2__ {int (* read ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CY_DELAY_DFLT ; 
 int CY_NUM_RETRY ; 
 int EIO ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static int ttsp_read_block_data(struct cyttsp *ts, u8 command,
				u8 length, void *buf)
{
	int error;
	int tries;

	for (tries = 0; tries < CY_NUM_RETRY; tries++) {
		error = ts->bus_ops->read(ts->dev, ts->xfer_buf, command,
				length, buf);
		if (!error)
			return 0;

		msleep(CY_DELAY_DFLT);
	}

	return -EIO;
}