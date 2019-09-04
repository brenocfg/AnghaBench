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
typedef  int u8 ;
struct mxt_data {int max_reportid; int update_input; TYPE_1__* client; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/  mxt_input_sync (struct mxt_data*) ; 
 int mxt_read_and_process_messages (struct mxt_data*,int) ; 

__attribute__((used)) static int mxt_process_messages_until_invalid(struct mxt_data *data)
{
	struct device *dev = &data->client->dev;
	int count, read;
	u8 tries = 2;

	count = data->max_reportid;

	/* Read messages until we force an invalid */
	do {
		read = mxt_read_and_process_messages(data, count);
		if (read < count)
			return 0;
	} while (--tries);

	if (data->update_input) {
		mxt_input_sync(data);
		data->update_input = false;
	}

	dev_err(dev, "CHG pin isn't cleared\n");
	return -EBUSY;
}