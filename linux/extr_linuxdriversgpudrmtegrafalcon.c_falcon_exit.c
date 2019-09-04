#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * vaddr; int /*<<< orphan*/  paddr; int /*<<< orphan*/  size; int /*<<< orphan*/ * firmware; } ;
struct falcon {TYPE_1__ firmware; TYPE_2__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* free ) (struct falcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct falcon*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void falcon_exit(struct falcon *falcon)
{
	if (falcon->firmware.firmware) {
		release_firmware(falcon->firmware.firmware);
		falcon->firmware.firmware = NULL;
	}

	if (falcon->firmware.vaddr) {
		falcon->ops->free(falcon, falcon->firmware.size,
				  falcon->firmware.paddr,
				  falcon->firmware.vaddr);
		falcon->firmware.vaddr = NULL;
	}
}