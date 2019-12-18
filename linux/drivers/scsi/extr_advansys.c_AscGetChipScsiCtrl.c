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
typedef  scalar_t__ PortAddr ;

/* Variables and functions */
 int /*<<< orphan*/  AscSetBank (scalar_t__,int) ; 
 scalar_t__ IOP_REG_SC ; 
 unsigned char inp (scalar_t__) ; 

__attribute__((used)) static unsigned char AscGetChipScsiCtrl(PortAddr iop_base)
{
	unsigned char sc;

	AscSetBank(iop_base, 1);
	sc = inp(iop_base + IOP_REG_SC);
	AscSetBank(iop_base, 0);
	return sc;
}