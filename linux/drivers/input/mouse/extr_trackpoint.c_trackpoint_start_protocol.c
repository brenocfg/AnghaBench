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
struct psmouse {int /*<<< orphan*/  ps2dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  MAKE_PS2_CMD (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TP_READ_ID ; 
#define  TP_VARIANT_ALPS 131 
#define  TP_VARIANT_ELAN 130 
#define  TP_VARIANT_IBM 129 
#define  TP_VARIANT_NXP 128 
 int ps2_command (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int trackpoint_start_protocol(struct psmouse *psmouse,
				     u8 *variant_id, u8 *firmware_id)
{
	u8 param[2] = { 0 };
	int error;

	error = ps2_command(&psmouse->ps2dev,
			    param, MAKE_PS2_CMD(0, 2, TP_READ_ID));
	if (error)
		return error;

	switch (param[0]) {
	case TP_VARIANT_IBM:
	case TP_VARIANT_ALPS:
	case TP_VARIANT_ELAN:
	case TP_VARIANT_NXP:
		if (variant_id)
			*variant_id = param[0];
		if (firmware_id)
			*firmware_id = param[1];
		return 0;
	}

	return -ENODEV;
}