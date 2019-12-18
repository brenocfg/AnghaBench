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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GPIO_1B ; 
 int /*<<< orphan*/  GPIO_3 ; 
 int /*<<< orphan*/  GPIO_3B ; 
 int /*<<< orphan*/  GPIO_4 ; 
 int /*<<< orphan*/  GPIO_4B ; 
 scalar_t__ MXL_ControlWrite (struct dvb_frontend*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u16 MXL_SetGPIO(struct dvb_frontend *fe, u8 GPIO_Num, u8 GPIO_Val)
{
	u16 status = 0;

	if (GPIO_Num == 1)
		status += MXL_ControlWrite(fe, GPIO_1B, GPIO_Val ? 0 : 1);

	/* GPIO2 is not available */

	if (GPIO_Num == 3) {
		if (GPIO_Val == 1) {
			status += MXL_ControlWrite(fe, GPIO_3, 0);
			status += MXL_ControlWrite(fe, GPIO_3B, 0);
		}
		if (GPIO_Val == 0) {
			status += MXL_ControlWrite(fe, GPIO_3, 1);
			status += MXL_ControlWrite(fe, GPIO_3B, 1);
		}
		if (GPIO_Val == 3) { /* tri-state */
			status += MXL_ControlWrite(fe, GPIO_3, 0);
			status += MXL_ControlWrite(fe, GPIO_3B, 1);
		}
	}
	if (GPIO_Num == 4) {
		if (GPIO_Val == 1) {
			status += MXL_ControlWrite(fe, GPIO_4, 0);
			status += MXL_ControlWrite(fe, GPIO_4B, 0);
		}
		if (GPIO_Val == 0) {
			status += MXL_ControlWrite(fe, GPIO_4, 1);
			status += MXL_ControlWrite(fe, GPIO_4B, 1);
		}
		if (GPIO_Val == 3) { /* tri-state */
			status += MXL_ControlWrite(fe, GPIO_4, 0);
			status += MXL_ControlWrite(fe, GPIO_4B, 1);
		}
	}

	return status;
}