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
struct steam_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  client_opened; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct steam_device* input_get_drvdata (struct input_dev*) ; 
 scalar_t__ lizard_mode ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  steam_set_lizard_mode (struct steam_device*,int) ; 

__attribute__((used)) static int steam_input_open(struct input_dev *dev)
{
	struct steam_device *steam = input_get_drvdata(dev);

	mutex_lock(&steam->mutex);
	if (!steam->client_opened && lizard_mode)
		steam_set_lizard_mode(steam, false);
	mutex_unlock(&steam->mutex);
	return 0;
}