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
struct dm_exception {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  exception_cache ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct dm_exception*) ; 

__attribute__((used)) static void free_completed_exception(struct dm_exception *e)
{
	kmem_cache_free(exception_cache, e);
}