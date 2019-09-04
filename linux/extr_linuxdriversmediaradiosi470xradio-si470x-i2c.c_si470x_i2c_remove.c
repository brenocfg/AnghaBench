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
struct si470x_device {int /*<<< orphan*/  videodev; } ;
struct i2c_client {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct si470x_device*) ; 
 struct si470x_device* i2c_get_clientdata (struct i2c_client*) ; 
 int /*<<< orphan*/  kfree (struct si470x_device*) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int si470x_i2c_remove(struct i2c_client *client)
{
	struct si470x_device *radio = i2c_get_clientdata(client);

	free_irq(client->irq, radio);
	video_unregister_device(&radio->videodev);
	kfree(radio);

	return 0;
}