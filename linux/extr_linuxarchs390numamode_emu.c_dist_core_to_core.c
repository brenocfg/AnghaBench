#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct toptree {int dummy; } ;
struct TYPE_6__ {scalar_t__ id; } ;
struct TYPE_5__ {scalar_t__ id; } ;
struct TYPE_4__ {scalar_t__ id; } ;

/* Variables and functions */
 int DIST_BOOK ; 
 int DIST_CORE ; 
 int DIST_DRAWER ; 
 int DIST_MC ; 
 TYPE_3__* core_book (struct toptree*) ; 
 TYPE_2__* core_drawer (struct toptree*) ; 
 TYPE_1__* core_mc (struct toptree*) ; 

__attribute__((used)) static int dist_core_to_core(struct toptree *core1, struct toptree *core2)
{
	if (core_drawer(core1)->id != core_drawer(core2)->id)
		return DIST_DRAWER;
	if (core_book(core1)->id != core_book(core2)->id)
		return DIST_BOOK;
	if (core_mc(core1)->id != core_mc(core2)->id)
		return DIST_MC;
	/* Same core or sibling on same MC */
	return DIST_CORE;
}