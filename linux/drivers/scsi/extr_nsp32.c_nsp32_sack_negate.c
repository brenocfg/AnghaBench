#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int BaseAddress; } ;
typedef  TYPE_1__ nsp32_hw_data ;

/* Variables and functions */
 unsigned char BUSCTL_ACK ; 
 int /*<<< orphan*/  SCSI_BUS_CONTROL ; 
 unsigned char nsp32_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_write1 (unsigned int,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void nsp32_sack_negate(nsp32_hw_data *data)
{
	unsigned int  base = data->BaseAddress;
	unsigned char busctrl;

	busctrl  = nsp32_read1(base, SCSI_BUS_CONTROL);
	busctrl	&= ~BUSCTL_ACK;
	nsp32_write1(base, SCSI_BUS_CONTROL, busctrl);
}