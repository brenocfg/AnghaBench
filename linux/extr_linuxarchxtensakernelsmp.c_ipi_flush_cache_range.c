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
struct flush_data {int /*<<< orphan*/  addr2; int /*<<< orphan*/  addr1; int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_flush_cache_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipi_flush_cache_range(void *arg)
{
	struct flush_data *fd = arg;
	local_flush_cache_range(fd->vma, fd->addr1, fd->addr2);
}