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
struct usba_udc {TYPE_1__* errata; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* toggle_bias ) (struct usba_udc*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct usba_udc*,int) ; 

__attribute__((used)) static void toggle_bias(struct usba_udc *udc, int is_on)
{
	if (udc->errata && udc->errata->toggle_bias)
		udc->errata->toggle_bias(udc, is_on);
}