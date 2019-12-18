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
struct v4l2_capability {int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRIVER_CARD ; 
 int /*<<< orphan*/  DRIVER_NAME ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int si470x_vidioc_querycap(struct file *file, void *priv,
				  struct v4l2_capability *capability)
{
	strscpy(capability->driver, DRIVER_NAME, sizeof(capability->driver));
	strscpy(capability->card, DRIVER_CARD, sizeof(capability->card));
	return 0;
}