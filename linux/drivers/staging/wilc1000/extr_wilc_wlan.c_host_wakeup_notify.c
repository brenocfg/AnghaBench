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
struct wilc {TYPE_1__* hif_func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* hif_write_reg ) (struct wilc*,int,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WILC_BUS_ACQUIRE_ONLY ; 
 int /*<<< orphan*/  WILC_BUS_RELEASE_ONLY ; 
 int /*<<< orphan*/  acquire_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_bus (struct wilc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct wilc*,int,int) ; 

void host_wakeup_notify(struct wilc *wilc)
{
	acquire_bus(wilc, WILC_BUS_ACQUIRE_ONLY);
	wilc->hif_func->hif_write_reg(wilc, 0x10b0, 1);
	release_bus(wilc, WILC_BUS_RELEASE_ONLY);
}