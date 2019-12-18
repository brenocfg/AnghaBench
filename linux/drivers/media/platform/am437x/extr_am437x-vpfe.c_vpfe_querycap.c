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
struct TYPE_2__ {char* name; } ;
struct vpfe_device {TYPE_1__ v4l2_dev; } ;
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;

/* Variables and functions */
 char* VPFE_MODULE_NAME ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,char*,int) ; 
 struct vpfe_device* video_drvdata (struct file*) ; 
 int /*<<< orphan*/  vpfe_dbg (int,struct vpfe_device*,char*) ; 

__attribute__((used)) static int vpfe_querycap(struct file *file, void  *priv,
			 struct v4l2_capability *cap)
{
	struct vpfe_device *vpfe = video_drvdata(file);

	vpfe_dbg(2, vpfe, "vpfe_querycap\n");

	strscpy(cap->driver, VPFE_MODULE_NAME, sizeof(cap->driver));
	strscpy(cap->card, "TI AM437x VPFE", sizeof(cap->card));
	snprintf(cap->bus_info, sizeof(cap->bus_info),
			"platform:%s", vpfe->v4l2_dev.name);
	return 0;
}