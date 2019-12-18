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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  FLEX10 ; 
 int /*<<< orphan*/  MC_NONE ; 
 int QNQ_MODE ; 
 int /*<<< orphan*/  UMC ; 
 int UMC_ENABLED ; 
 int VNIC_MODE ; 
 int /*<<< orphan*/  vNIC1 ; 
 int /*<<< orphan*/  vNIC2 ; 

__attribute__((used)) static u8 be_convert_mc_type(u32 function_mode)
{
	if (function_mode & VNIC_MODE && function_mode & QNQ_MODE)
		return vNIC1;
	else if (function_mode & QNQ_MODE)
		return FLEX10;
	else if (function_mode & VNIC_MODE)
		return vNIC2;
	else if (function_mode & UMC_ENABLED)
		return UMC;
	else
		return MC_NONE;
}