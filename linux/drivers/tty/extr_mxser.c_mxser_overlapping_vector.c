#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mxser_board {scalar_t__ vector; TYPE_2__* info; TYPE_1__* ports; } ;
struct TYPE_4__ {int nports; } ;
struct TYPE_3__ {scalar_t__ ioaddr; } ;

/* Variables and functions */
 scalar_t__ allow_overlapping_vector ; 

__attribute__((used)) static bool mxser_overlapping_vector(struct mxser_board *brd)
{
	return allow_overlapping_vector &&
		brd->vector >= brd->ports[0].ioaddr &&
		brd->vector < brd->ports[0].ioaddr + 8 * brd->info->nports;
}