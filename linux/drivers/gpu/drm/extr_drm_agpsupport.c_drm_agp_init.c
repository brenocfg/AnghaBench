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
struct drm_device {int /*<<< orphan*/  pdev; } ;
struct TYPE_2__ {scalar_t__ chipset; int /*<<< orphan*/  aper_base; int /*<<< orphan*/  page_mask; int /*<<< orphan*/  cant_use_aperture; } ;
struct drm_agp_head {TYPE_1__ agp_info; int /*<<< orphan*/  base; int /*<<< orphan*/  page_mask; int /*<<< orphan*/  cant_use_aperture; int /*<<< orphan*/  memory; scalar_t__ bridge; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ NOT_SUPPORTED ; 
 scalar_t__ agp_backend_acquire (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  agp_backend_release (scalar_t__) ; 
 int /*<<< orphan*/  agp_copy_info (scalar_t__,TYPE_1__*) ; 
 scalar_t__ agp_find_bridge (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct drm_agp_head*) ; 
 struct drm_agp_head* kzalloc (int,int /*<<< orphan*/ ) ; 

struct drm_agp_head *drm_agp_init(struct drm_device *dev)
{
	struct drm_agp_head *head = NULL;

	head = kzalloc(sizeof(*head), GFP_KERNEL);
	if (!head)
		return NULL;
	head->bridge = agp_find_bridge(dev->pdev);
	if (!head->bridge) {
		head->bridge = agp_backend_acquire(dev->pdev);
		if (!head->bridge) {
			kfree(head);
			return NULL;
		}
		agp_copy_info(head->bridge, &head->agp_info);
		agp_backend_release(head->bridge);
	} else {
		agp_copy_info(head->bridge, &head->agp_info);
	}
	if (head->agp_info.chipset == NOT_SUPPORTED) {
		kfree(head);
		return NULL;
	}
	INIT_LIST_HEAD(&head->memory);
	head->cant_use_aperture = head->agp_info.cant_use_aperture;
	head->page_mask = head->agp_info.page_mask;
	head->base = head->agp_info.aper_base;
	return head;
}