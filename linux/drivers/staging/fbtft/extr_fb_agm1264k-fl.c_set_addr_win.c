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
struct fbtft_par {int dummy; } ;
struct TYPE_2__ {int xs; int ys_page; int xe; int ye_page; } ;

/* Variables and functions */
 TYPE_1__ addr_win ; 

__attribute__((used)) static void set_addr_win(struct fbtft_par *par, int xs, int ys, int xe, int ye)
{
	addr_win.xs = xs;
	addr_win.ys_page = ys / 8;
	addr_win.xe = xe;
	addr_win.ye_page = ye / 8;
}