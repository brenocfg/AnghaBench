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
typedef  void* u8 ;
struct psmouse {int oob_data_type; void* extra_buttons; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  PSMOUSE_OOB_EXTRA_BTNS 129 
#define  PSMOUSE_OOB_NONE 128 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_report_standard_buttons (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*,int) ; 

__attribute__((used)) static void psmouse_handle_oob_data(struct psmouse *psmouse, u8 data)
{
	switch (psmouse->oob_data_type) {
	case PSMOUSE_OOB_NONE:
		psmouse->oob_data_type = data;
		break;

	case PSMOUSE_OOB_EXTRA_BTNS:
		psmouse_report_standard_buttons(psmouse->dev, data);
		input_sync(psmouse->dev);

		psmouse->extra_buttons = data;
		psmouse->oob_data_type = PSMOUSE_OOB_NONE;
		break;

	default:
		psmouse_warn(psmouse,
			     "unknown OOB_DATA type: 0x%02x\n",
			     psmouse->oob_data_type);
		psmouse->oob_data_type = PSMOUSE_OOB_NONE;
		break;
	}
}