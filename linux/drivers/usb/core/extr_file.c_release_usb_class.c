#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct kref {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  class; } ;

/* Variables and functions */
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 TYPE_1__* usb_class ; 

__attribute__((used)) static void release_usb_class(struct kref *kref)
{
	/* Ok, we cheat as we know we only have one usb_class */
	class_destroy(usb_class->class);
	kfree(usb_class);
	usb_class = NULL;
}