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
struct ttm_tt {int /*<<< orphan*/ * func; } ;
struct radeon_ttm_tt {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  radeon_backend_func ; 

__attribute__((used)) static struct radeon_ttm_tt *radeon_ttm_tt_to_gtt(struct ttm_tt *ttm)
{
	if (!ttm || ttm->func != &radeon_backend_func)
		return NULL;
	return (struct radeon_ttm_tt *)ttm;
}