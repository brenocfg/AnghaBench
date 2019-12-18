#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
typedef  enum tiler_fmt { ____Placeholder_tiler_fmt } tiler_fmt ;
struct TYPE_2__ {size_t cpp; } ;

/* Variables and functions */
 TYPE_1__* geom ; 
 int /*<<< orphan*/  tiler_align (int,size_t*,size_t*) ; 

size_t tiler_size(enum tiler_fmt fmt, u16 w, u16 h)
{
	tiler_align(fmt, &w, &h);
	return geom[fmt].cpp * w * h;
}