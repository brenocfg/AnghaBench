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
typedef  int /*<<< orphan*/  cxio_hal_ev_callback_func_t ;

/* Variables and functions */
 int /*<<< orphan*/ * cxio_ev_cb ; 

void cxio_unregister_ev_cb(cxio_hal_ev_callback_func_t ev_cb)
{
	cxio_ev_cb = NULL;
}