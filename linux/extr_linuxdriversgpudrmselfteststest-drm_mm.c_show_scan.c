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
struct drm_mm_scan {int /*<<< orphan*/  color; int /*<<< orphan*/  alignment; int /*<<< orphan*/  size; int /*<<< orphan*/  hit_end; int /*<<< orphan*/  hit_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_scan(const struct drm_mm_scan *scan)
{
	pr_info("scan: hit [%llx, %llx], size=%lld, align=%lld, color=%ld\n",
		scan->hit_start, scan->hit_end,
		scan->size, scan->alignment, scan->color);
}