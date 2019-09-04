#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct video_i2c_data {TYPE_1__ vdev; TYPE_3__ v4l2_dev; struct i2c_client* client; } ;
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct i2c_client {int addr; TYPE_2__* adapter; } ;
struct file {int dummy; } ;
struct TYPE_5__ {int nr; } ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct video_i2c_data* video_drvdata (struct file*) ; 

__attribute__((used)) static int video_i2c_querycap(struct file *file, void  *priv,
				struct v4l2_capability *vcap)
{
	struct video_i2c_data *data = video_drvdata(file);
	struct i2c_client *client = data->client;

	strlcpy(vcap->driver, data->v4l2_dev.name, sizeof(vcap->driver));
	strlcpy(vcap->card, data->vdev.name, sizeof(vcap->card));

	sprintf(vcap->bus_info, "I2C:%d-%d", client->adapter->nr, client->addr);

	return 0;
}