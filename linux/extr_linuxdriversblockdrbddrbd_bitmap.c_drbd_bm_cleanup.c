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
struct drbd_device {TYPE_1__* bitmap; } ;
struct TYPE_3__ {int /*<<< orphan*/  bm_pages; int /*<<< orphan*/  bm_number_of_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  bm_free_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bm_vk_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

void drbd_bm_cleanup(struct drbd_device *device)
{
	if (!expect(device->bitmap))
		return;
	bm_free_pages(device->bitmap->bm_pages, device->bitmap->bm_number_of_pages);
	bm_vk_free(device->bitmap->bm_pages);
	kfree(device->bitmap);
	device->bitmap = NULL;
}