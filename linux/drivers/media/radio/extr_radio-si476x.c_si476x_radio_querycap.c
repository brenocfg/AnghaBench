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
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct TYPE_2__ {char* name; } ;
struct si476x_radio {TYPE_1__ v4l2dev; } ;
struct file {int dummy; } ;

/* Variables and functions */
 char* DRIVER_CARD ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct si476x_radio* video_drvdata (struct file*) ; 

__attribute__((used)) static int si476x_radio_querycap(struct file *file, void *priv,
				 struct v4l2_capability *capability)
{
	struct si476x_radio *radio = video_drvdata(file);

	strscpy(capability->driver, radio->v4l2dev.name,
		sizeof(capability->driver));
	strscpy(capability->card,   DRIVER_CARD, sizeof(capability->card));
	snprintf(capability->bus_info, sizeof(capability->bus_info),
		 "platform:%s", radio->v4l2dev.name);
	return 0;
}