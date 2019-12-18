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
typedef  void* u32 ;
struct lpi_range {void* span; void* base_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct lpi_range* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct lpi_range *mk_lpi_range(u32 base, u32 span)
{
	struct lpi_range *range;

	range = kmalloc(sizeof(*range), GFP_KERNEL);
	if (range) {
		range->base_id = base;
		range->span = span;
	}

	return range;
}