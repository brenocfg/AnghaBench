#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dscr_nxtptr; } ;
typedef  TYPE_1__ au1x_ddma_desc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DSCR_GET_NXTPTR (int /*<<< orphan*/ ) ; 
 void* phys_to_virt (int /*<<< orphan*/ ) ; 

void *au1xxx_ddma_get_nextptr_virt(au1x_ddma_desc_t *dp)
{
	return phys_to_virt(DSCR_GET_NXTPTR(dp->dscr_nxtptr));
}