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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */
 int DT_CS ; 
 int DT_IN ; 
 int SROM_RD ; 
 int SROM_SR ; 
 int /*<<< orphan*/  sendto_srom (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srom_address (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srom_command (int,int /*<<< orphan*/ ) ; 
 short srom_data (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srom_latch (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static short
srom_rd(u_long addr, u_char offset)
{
    sendto_srom(SROM_RD | SROM_SR, addr);

    srom_latch(SROM_RD | SROM_SR | DT_CS, addr);
    srom_command(SROM_RD | SROM_SR | DT_IN | DT_CS, addr);
    srom_address(SROM_RD | SROM_SR | DT_CS, addr, offset);

    return srom_data(SROM_RD | SROM_SR | DT_CS, addr);
}