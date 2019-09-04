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
struct qxl_device {int dummy; } ;
struct qxl_bo {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  QXL_GEM_DOMAIN_VRAM ; 
 int qxl_bo_create (struct qxl_device*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct qxl_bo**) ; 

__attribute__((used)) static int qxl_release_bo_alloc(struct qxl_device *qdev,
				struct qxl_bo **bo)
{
	/* pin releases bo's they are too messy to evict */
	return qxl_bo_create(qdev, PAGE_SIZE, false, true,
			     QXL_GEM_DOMAIN_VRAM, NULL, bo);
}