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
struct drm_device {int /*<<< orphan*/  clientlist_mutex; int /*<<< orphan*/  clientlist; } ;
struct drm_client_dev {int /*<<< orphan*/  list; struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void drm_client_register(struct drm_client_dev *client)
{
	struct drm_device *dev = client->dev;

	mutex_lock(&dev->clientlist_mutex);
	list_add(&client->list, &dev->clientlist);
	mutex_unlock(&dev->clientlist_mutex);
}