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
struct agp_controller {int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct agp_controller* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct agp_controller *agp_create_controller(pid_t id)
{
	struct agp_controller *controller;

	controller = kzalloc(sizeof(struct agp_controller), GFP_KERNEL);
	if (controller == NULL)
		return NULL;

	controller->pid = id;
	return controller;
}