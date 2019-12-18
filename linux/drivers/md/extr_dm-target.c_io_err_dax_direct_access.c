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
struct dm_target {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
typedef  int /*<<< orphan*/  pfn_t ;

/* Variables and functions */
 long EIO ; 

__attribute__((used)) static long io_err_dax_direct_access(struct dm_target *ti, pgoff_t pgoff,
		long nr_pages, void **kaddr, pfn_t *pfn)
{
	return -EIO;
}