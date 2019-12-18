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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  SISIOADDRESS ;

/* Variables and functions */
 int /*<<< orphan*/  SiS_GetReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
SiS_SetRegAND(SISIOADDRESS Port, u8 Index, u8 DataAND)
{
   u8 temp;

   temp = SiS_GetReg(Port, Index);
   temp &= DataAND;
   SiS_SetReg(Port, Index, temp);
}