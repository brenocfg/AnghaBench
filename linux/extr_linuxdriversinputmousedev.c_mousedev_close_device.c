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
struct mousedev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  handle; int /*<<< orphan*/  open; scalar_t__ exist; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_close_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mousedev_close_device(struct mousedev *mousedev)
{
	mutex_lock(&mousedev->mutex);

	if (mousedev->exist && !--mousedev->open)
		input_close_device(&mousedev->handle);

	mutex_unlock(&mousedev->mutex);
}