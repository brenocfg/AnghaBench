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
typedef  int /*<<< orphan*/  u_long ;
typedef  int u_int ;

/* Variables and functions */
 int DT_CLK ; 
 int /*<<< orphan*/  sendto_srom (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
srom_latch(u_int command, u_long addr)
{
    sendto_srom(command, addr);
    sendto_srom(command | DT_CLK, addr);
    sendto_srom(command, addr);
}