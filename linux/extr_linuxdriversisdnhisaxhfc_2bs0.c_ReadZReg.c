#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct BCState {TYPE_1__* cs; } ;
struct TYPE_4__ {int (* BC_Read_Reg ) (TYPE_1__*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int HFC_CIP ; 
 int /*<<< orphan*/  HFC_DATA ; 
 int HFC_Z_HIGH ; 
 int HFC_Z_LOW ; 
 int /*<<< orphan*/  WaitNoBusy (TYPE_1__*) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int stub2 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ReadZReg(struct BCState *bcs, u_char reg)
{
	int val;

	WaitNoBusy(bcs->cs);
	val = 256 * bcs->cs->BC_Read_Reg(bcs->cs, HFC_DATA, reg | HFC_CIP | HFC_Z_HIGH);
	WaitNoBusy(bcs->cs);
	val += bcs->cs->BC_Read_Reg(bcs->cs, HFC_DATA, reg | HFC_CIP | HFC_Z_LOW);
	return (val);
}