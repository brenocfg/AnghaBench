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
struct wm97xx {int* dig; } ;

/* Variables and functions */
 int WM9713_PDEN ; 

__attribute__((used)) static inline int is_pden(struct wm97xx *wm)
{
	return wm->dig[2] & WM9713_PDEN;
}