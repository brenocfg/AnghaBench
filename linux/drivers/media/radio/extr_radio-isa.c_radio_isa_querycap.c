#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_capability {int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct TYPE_5__ {char* name; } ;
struct radio_isa_card {TYPE_1__ v4l2_dev; TYPE_4__* drv; } ;
struct file {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__ driver; } ;
struct TYPE_8__ {int /*<<< orphan*/  card; TYPE_3__ driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  strscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct radio_isa_card* video_drvdata (struct file*) ; 

__attribute__((used)) static int radio_isa_querycap(struct file *file, void  *priv,
					struct v4l2_capability *v)
{
	struct radio_isa_card *isa = video_drvdata(file);

	strscpy(v->driver, isa->drv->driver.driver.name, sizeof(v->driver));
	strscpy(v->card, isa->drv->card, sizeof(v->card));
	snprintf(v->bus_info, sizeof(v->bus_info), "ISA:%s", isa->v4l2_dev.name);
	return 0;
}