#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dev_groups; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 TYPE_1__* class_create (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* extcon_class ; 
 int /*<<< orphan*/  extcon_groups ; 

__attribute__((used)) static int create_extcon_class(void)
{
	if (!extcon_class) {
		extcon_class = class_create(THIS_MODULE, "extcon");
		if (IS_ERR(extcon_class))
			return PTR_ERR(extcon_class);
		extcon_class->dev_groups = extcon_groups;
	}

	return 0;
}