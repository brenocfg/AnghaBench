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
struct capi_ctr {int dummy; } ;
typedef  int /*<<< orphan*/  capiloaddata ;

/* Variables and functions */

__attribute__((used)) static int hycapi_load_firmware(struct capi_ctr *ctrl, capiloaddata *data)
{
#ifdef HYCAPI_PRINTFNAMES
	printk(KERN_NOTICE "hycapi_load_firmware\n");
#endif
	return 0;
}