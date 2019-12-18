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
typedef  int u8 ;
typedef  int /*<<< orphan*/  SISIOADDRESS ;

/* Variables and functions */
 int SiS_GetReg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiS_SetReg (int /*<<< orphan*/ ,int,int) ; 

void
SiS_SetRegANDOR(SISIOADDRESS Port, u8 Index, u8 DataAND, u8 DataOR)
{
   u8 temp;

   temp = SiS_GetReg(Port, Index);
   temp = (temp & (DataAND)) | DataOR;
   SiS_SetReg(Port, Index, temp);
}