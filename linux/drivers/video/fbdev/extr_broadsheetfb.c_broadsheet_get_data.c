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
typedef  int /*<<< orphan*/  u16 ;
struct broadsheetfb_par {TYPE_1__* board; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* mmio_read ) (struct broadsheetfb_par*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  broadsheet_gpio_get_data (struct broadsheetfb_par*) ; 
 int /*<<< orphan*/  stub1 (struct broadsheetfb_par*) ; 

__attribute__((used)) static u16 broadsheet_get_data(struct broadsheetfb_par *par)
{
	if (par->board->mmio_read)
		return par->board->mmio_read(par);
	else
		return broadsheet_gpio_get_data(par);
}