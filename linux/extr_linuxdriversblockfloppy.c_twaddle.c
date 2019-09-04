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
struct TYPE_6__ {scalar_t__ select_delay; } ;
struct TYPE_5__ {int /*<<< orphan*/  select_date; } ;
struct TYPE_4__ {int dor; } ;

/* Variables and functions */
 TYPE_3__* DP ; 
 TYPE_2__* DRS ; 
 TYPE_1__* FDCS ; 
 int /*<<< orphan*/  FD_DOR ; 
 int UNIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_drive ; 
 int /*<<< orphan*/  fd_outb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static void twaddle(void)
{
	if (DP->select_delay)
		return;
	fd_outb(FDCS->dor & ~(0x10 << UNIT(current_drive)), FD_DOR);
	fd_outb(FDCS->dor, FD_DOR);
	DRS->select_date = jiffies;
}