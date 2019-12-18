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
struct usb_function {int dummy; } ;
struct f_uas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct f_uas*) ; 
 struct f_uas* to_f_uas (struct usb_function*) ; 

__attribute__((used)) static void tcm_free(struct usb_function *f)
{
	struct f_uas *tcm = to_f_uas(f);

	kfree(tcm);
}