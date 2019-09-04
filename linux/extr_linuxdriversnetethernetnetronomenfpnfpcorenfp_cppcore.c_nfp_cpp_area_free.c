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
struct nfp_cpp_area {int /*<<< orphan*/  cpp; int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfp_cpp_area_put (struct nfp_cpp_area*) ; 
 int /*<<< orphan*/  nfp_warn (int /*<<< orphan*/ ,char*) ; 

void nfp_cpp_area_free(struct nfp_cpp_area *area)
{
	if (atomic_read(&area->refcount))
		nfp_warn(area->cpp, "Warning: freeing busy area\n");
	nfp_cpp_area_put(area);
}