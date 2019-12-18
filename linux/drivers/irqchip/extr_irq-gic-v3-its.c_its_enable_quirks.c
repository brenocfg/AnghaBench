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
typedef  int /*<<< orphan*/  u32 ;
struct its_node {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ GITS_IIDR ; 
 int /*<<< orphan*/  gic_enable_quirks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct its_node*) ; 
 int /*<<< orphan*/  its_quirks ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 

__attribute__((used)) static void its_enable_quirks(struct its_node *its)
{
	u32 iidr = readl_relaxed(its->base + GITS_IIDR);

	gic_enable_quirks(iidr, its_quirks, its);
}