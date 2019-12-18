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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct vme_master_resource {TYPE_1__ bus_resource; int /*<<< orphan*/ * kern_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  release_resource (TYPE_1__*) ; 

__attribute__((used)) static void tsi148_free_resource(struct vme_master_resource *image)
{
	iounmap(image->kern_base);
	image->kern_base = NULL;
	release_resource(&image->bus_resource);
	kfree(image->bus_resource.name);
	memset(&image->bus_resource, 0, sizeof(image->bus_resource));
}