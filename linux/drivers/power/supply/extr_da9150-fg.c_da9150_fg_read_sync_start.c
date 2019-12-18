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
typedef  scalar_t__ u32 ;
struct da9150_fg {int /*<<< orphan*/  dev; int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9150_QIF_SYNC ; 
 int /*<<< orphan*/  DA9150_QIF_SYNC_RETRIES ; 
 int /*<<< orphan*/  DA9150_QIF_SYNC_SIZE ; 
 int DA9150_QIF_SYNC_TIMEOUT ; 
 scalar_t__ da9150_fg_read_attr (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  da9150_fg_write_attr (struct da9150_fg*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static void da9150_fg_read_sync_start(struct da9150_fg *fg)
{
	int i = 0;
	u32 res = 0;

	mutex_lock(&fg->io_lock);

	/* Check if QIF sync already requested, and write to sync if not */
	res = da9150_fg_read_attr(fg, DA9150_QIF_SYNC,
				  DA9150_QIF_SYNC_SIZE);
	if (res > 0)
		da9150_fg_write_attr(fg, DA9150_QIF_SYNC,
				     DA9150_QIF_SYNC_SIZE, 0);

	/* Wait for sync to complete */
	res = 0;
	while ((res == 0) && (i++ < DA9150_QIF_SYNC_RETRIES)) {
		usleep_range(DA9150_QIF_SYNC_TIMEOUT,
			     DA9150_QIF_SYNC_TIMEOUT * 2);
		res = da9150_fg_read_attr(fg, DA9150_QIF_SYNC,
					  DA9150_QIF_SYNC_SIZE);
	}

	/* Check if sync completed */
	if (res == 0)
		dev_err(fg->dev, "Failed to perform QIF read sync!\n");
}