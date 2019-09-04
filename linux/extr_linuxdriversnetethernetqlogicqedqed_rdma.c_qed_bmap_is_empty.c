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
struct qed_bmap {scalar_t__ max_count; int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 scalar_t__ find_first_bit (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static bool qed_bmap_is_empty(struct qed_bmap *bmap)
{
	return bmap->max_count == find_first_bit(bmap->bitmap, bmap->max_count);
}