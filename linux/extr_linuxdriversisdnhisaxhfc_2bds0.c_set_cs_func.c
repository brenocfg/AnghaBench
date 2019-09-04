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
struct IsdnCardState {int /*<<< orphan*/  tqueue; int /*<<< orphan*/  dbusytimer; int /*<<< orphan*/ * BC_Write_Reg; int /*<<< orphan*/ * BC_Read_Reg; int /*<<< orphan*/ * writeisacfifo; int /*<<< orphan*/ * readisacfifo; int /*<<< orphan*/ * writeisac; int /*<<< orphan*/ * readisac; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReadReg ; 
 int /*<<< orphan*/  WriteReg ; 
 int /*<<< orphan*/  dummyf ; 
 int /*<<< orphan*/  hfc_dbusy_timer ; 
 int /*<<< orphan*/  hfcd_bh ; 
 int /*<<< orphan*/  readreghfcd ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writereghfcd ; 

void
set_cs_func(struct IsdnCardState *cs)
{
	cs->readisac = &readreghfcd;
	cs->writeisac = &writereghfcd;
	cs->readisacfifo = &dummyf;
	cs->writeisacfifo = &dummyf;
	cs->BC_Read_Reg = &ReadReg;
	cs->BC_Write_Reg = &WriteReg;
	timer_setup(&cs->dbusytimer, hfc_dbusy_timer, 0);
	INIT_WORK(&cs->tqueue, hfcd_bh);
}