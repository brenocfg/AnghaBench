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
struct radio_tea5777 {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; TYPE_1__* v4l2_dev; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcat (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct radio_tea5777* video_drvdata (struct file*) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
					struct v4l2_capability *v)
{
	struct radio_tea5777 *tea = video_drvdata(file);

	strscpy(v->driver, tea->v4l2_dev->name, sizeof(v->driver));
	strscpy(v->card, tea->card, sizeof(v->card));
	strlcat(v->card, " TEA5777", sizeof(v->card));
	strscpy(v->bus_info, tea->bus_info, sizeof(v->bus_info));
	return 0;
}