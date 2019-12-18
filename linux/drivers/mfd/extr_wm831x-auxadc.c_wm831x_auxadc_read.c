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
struct wm831x {int (* auxadc_read ) (struct wm831x*,int) ;} ;
typedef  enum wm831x_auxadc { ____Placeholder_wm831x_auxadc } wm831x_auxadc ;

/* Variables and functions */
 int stub1 (struct wm831x*,int) ; 

int wm831x_auxadc_read(struct wm831x *wm831x, enum wm831x_auxadc input)
{
	return wm831x->auxadc_read(wm831x, input);
}