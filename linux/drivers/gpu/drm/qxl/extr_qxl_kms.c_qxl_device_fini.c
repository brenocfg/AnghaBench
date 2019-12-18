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
struct qxl_device {int /*<<< orphan*/ * rom; int /*<<< orphan*/ * ram_header; int /*<<< orphan*/  vram_mapping; int /*<<< orphan*/  surface_mapping; int /*<<< orphan*/  release_ring; int /*<<< orphan*/  cursor_ring; int /*<<< orphan*/  command_ring; int /*<<< orphan*/  gc_work; int /*<<< orphan*/ * current_release_bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_mapping_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_bo_fini (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_bo_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qxl_gem_fini (struct qxl_device*) ; 
 int /*<<< orphan*/  qxl_ring_free (int /*<<< orphan*/ ) ; 

void qxl_device_fini(struct qxl_device *qdev)
{
	qxl_bo_unref(&qdev->current_release_bo[0]);
	qxl_bo_unref(&qdev->current_release_bo[1]);
	flush_work(&qdev->gc_work);
	qxl_ring_free(qdev->command_ring);
	qxl_ring_free(qdev->cursor_ring);
	qxl_ring_free(qdev->release_ring);
	qxl_gem_fini(qdev);
	qxl_bo_fini(qdev);
	io_mapping_free(qdev->surface_mapping);
	io_mapping_free(qdev->vram_mapping);
	iounmap(qdev->ram_header);
	iounmap(qdev->rom);
	qdev->rom = NULL;
}