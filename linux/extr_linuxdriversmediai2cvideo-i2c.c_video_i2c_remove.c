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
struct video_i2c_data {int /*<<< orphan*/  vdev; } ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 struct video_i2c_data* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int video_i2c_remove(struct i2c_client *client)
{
	struct video_i2c_data *data = i2c_get_clientdata(client);

	video_unregister_device(&data->vdev);

	return 0;
}