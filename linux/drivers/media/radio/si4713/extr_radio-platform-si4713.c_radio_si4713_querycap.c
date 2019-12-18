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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int radio_si4713_querycap(struct file *file, void *priv,
					struct v4l2_capability *capability)
{
	strscpy(capability->driver, "radio-si4713", sizeof(capability->driver));
	strscpy(capability->card, "Silicon Labs Si4713 Modulator",
		sizeof(capability->card));
	strscpy(capability->bus_info, "platform:radio-si4713",
		sizeof(capability->bus_info));
	return 0;
}