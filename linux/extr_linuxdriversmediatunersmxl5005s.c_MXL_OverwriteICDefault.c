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
typedef  int /*<<< orphan*/  u16 ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 scalar_t__ MXL_ControlWrite (struct dvb_frontend*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  OVERRIDE_1 ; 
 int /*<<< orphan*/  OVERRIDE_2 ; 
 int /*<<< orphan*/  OVERRIDE_3 ; 
 int /*<<< orphan*/  OVERRIDE_4 ; 

__attribute__((used)) static u16 MXL_OverwriteICDefault(struct dvb_frontend *fe)
{
	u16 status = 0;

	status += MXL_ControlWrite(fe, OVERRIDE_1, 1);
	status += MXL_ControlWrite(fe, OVERRIDE_2, 1);
	status += MXL_ControlWrite(fe, OVERRIDE_3, 1);
	status += MXL_ControlWrite(fe, OVERRIDE_4, 1);

	return status;
}