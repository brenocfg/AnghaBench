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
struct elan_tp_data {int /*<<< orphan*/  client; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* sleep_control ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int ETP_RETRY_COUNT ; 
 int /*<<< orphan*/  msleep (int) ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int elan_sleep(struct elan_tp_data *data)
{
	int repeat = ETP_RETRY_COUNT;
	int error;

	do {
		error = data->ops->sleep_control(data->client, true);
		if (!error)
			return 0;

		msleep(30);
	} while (--repeat > 0);

	return error;
}