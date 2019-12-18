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
typedef  int /*<<< orphan*/  uint32_t ;
struct dm_cache_policy {int /*<<< orphan*/  (* get_hint ) (struct dm_cache_policy*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct dm_cache_policy*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline uint32_t policy_get_hint(struct dm_cache_policy *p,
				       dm_cblock_t cblock)
{
	return p->get_hint ? p->get_hint(p, cblock) : 0;
}