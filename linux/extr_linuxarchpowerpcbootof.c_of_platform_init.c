#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  setprop; int /*<<< orphan*/  getprop; int /*<<< orphan*/  finddevice; } ;
struct TYPE_5__ {unsigned long initrd_addr; unsigned long initrd_size; void* promptr; } ;
struct TYPE_4__ {int /*<<< orphan*/  vmlinux_alloc; int /*<<< orphan*/  exit; int /*<<< orphan*/  malloc; int /*<<< orphan*/  image_hdr; } ;

/* Variables and functions */
 TYPE_3__ dt_ops ; 
 TYPE_2__ loader_info ; 
 int /*<<< orphan*/  of_console_init () ; 
 int /*<<< orphan*/  of_exit ; 
 int /*<<< orphan*/  of_finddevice ; 
 int /*<<< orphan*/  of_getprop ; 
 int /*<<< orphan*/  of_image_hdr ; 
 int /*<<< orphan*/  of_init (void*) ; 
 int /*<<< orphan*/  of_setprop ; 
 int /*<<< orphan*/  of_try_claim ; 
 int /*<<< orphan*/  of_vmlinux_alloc ; 
 TYPE_1__ platform_ops ; 

__attribute__((used)) static void of_platform_init(unsigned long a1, unsigned long a2, void *promptr)
{
	platform_ops.image_hdr = of_image_hdr;
	platform_ops.malloc = of_try_claim;
	platform_ops.exit = of_exit;
	platform_ops.vmlinux_alloc = of_vmlinux_alloc;

	dt_ops.finddevice = of_finddevice;
	dt_ops.getprop = of_getprop;
	dt_ops.setprop = of_setprop;

	of_console_init();

	of_init(promptr);
	loader_info.promptr = promptr;
	if (a1 && a2 && a2 != 0xdeadbeef) {
		loader_info.initrd_addr = a1;
		loader_info.initrd_size = a2;
	}
}