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
typedef  int u32 ;
struct guc_ct_pool_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct guc_ct_pool_entry*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void guc_ct_pool_entries_init(struct guc_ct_pool_entry *pool, u32 num)
{
	memset(pool, 0, num * sizeof(*pool));
}