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
struct mma9551_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int mma9551_read_version (int /*<<< orphan*/ ) ; 
 int mma9551_set_device_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mma9551_init(struct mma9551_data *data)
{
	int ret;

	ret = mma9551_read_version(data->client);
	if (ret)
		return ret;

	return mma9551_set_device_state(data->client, true);
}