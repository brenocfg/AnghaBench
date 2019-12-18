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
struct page {int dummy; } ;
struct nouveau_drm {scalar_t__ dmem; } ;

/* Variables and functions */
 scalar_t__ is_device_private_page (struct page*) ; 
 scalar_t__ page_to_dmem (struct page*) ; 

__attribute__((used)) static inline bool
nouveau_dmem_page(struct nouveau_drm *drm, struct page *page)
{
	return is_device_private_page(page) && drm->dmem == page_to_dmem(page);
}