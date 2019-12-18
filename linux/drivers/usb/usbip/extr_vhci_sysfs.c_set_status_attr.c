#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {TYPE_2__ attr; int /*<<< orphan*/  show; } ;
struct status_attr {TYPE_1__ attr; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ MAX_STATUS_NAME ; 
 int /*<<< orphan*/  S_IRUGO ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 struct status_attr* status_attrs ; 
 int /*<<< orphan*/  status_show ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

__attribute__((used)) static void set_status_attr(int id)
{
	struct status_attr *status;

	status = status_attrs + id;
	if (id == 0)
		strcpy(status->name, "status");
	else
		snprintf(status->name, MAX_STATUS_NAME+1, "status.%d", id);
	status->attr.attr.name = status->name;
	status->attr.attr.mode = S_IRUGO;
	status->attr.show = status_show;
	sysfs_attr_init(&status->attr.attr);
}