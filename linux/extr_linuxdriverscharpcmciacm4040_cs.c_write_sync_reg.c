#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reader_dev {TYPE_2__* p_dev; } ;
struct TYPE_4__ {TYPE_1__** resource; } ;
struct TYPE_3__ {int start; } ;

/* Variables and functions */
 scalar_t__ REG_OFFSET_SYNC_CONTROL ; 
 int wait_for_bulk_out_ready (struct reader_dev*) ; 
 int /*<<< orphan*/  xoutb (unsigned char,scalar_t__) ; 

__attribute__((used)) static int write_sync_reg(unsigned char val, struct reader_dev *dev)
{
	int iobase = dev->p_dev->resource[0]->start;
	int rc;

	rc = wait_for_bulk_out_ready(dev);
	if (rc <= 0)
		return rc;

	xoutb(val, iobase + REG_OFFSET_SYNC_CONTROL);
	rc = wait_for_bulk_out_ready(dev);
	if (rc <= 0)
		return rc;

	return 1;
}