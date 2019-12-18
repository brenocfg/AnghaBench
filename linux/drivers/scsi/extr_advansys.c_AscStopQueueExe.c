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
typedef  int /*<<< orphan*/  PortAddr ;

/* Variables and functions */
 int /*<<< orphan*/  ASCV_STOP_CODE_B ; 
 int ASC_STOP_ACK_RISC_STOP ; 
 int /*<<< orphan*/  ASC_STOP_REQ_RISC_STOP ; 
 int AscReadLramByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscWriteLramByte (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 

__attribute__((used)) static int AscStopQueueExe(PortAddr iop_base)
{
	int count = 0;

	if (AscReadLramByte(iop_base, ASCV_STOP_CODE_B) == 0) {
		AscWriteLramByte(iop_base, ASCV_STOP_CODE_B,
				 ASC_STOP_REQ_RISC_STOP);
		do {
			if (AscReadLramByte(iop_base, ASCV_STOP_CODE_B) &
			    ASC_STOP_ACK_RISC_STOP) {
				return (1);
			}
			mdelay(100);
		} while (count++ < 20);
	}
	return (0);
}