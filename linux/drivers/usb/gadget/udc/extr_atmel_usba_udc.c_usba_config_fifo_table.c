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
struct usba_udc {int /*<<< orphan*/ * fifo_cfg; } ;

/* Variables and functions */
 int ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  DBG_HW ; 
 int fifo_mode ; 
 void* mode_1_cfg ; 
 void* mode_2_cfg ; 
 void* mode_3_cfg ; 
 void* mode_4_cfg ; 

__attribute__((used)) static int usba_config_fifo_table(struct usba_udc *udc)
{
	int n;

	switch (fifo_mode) {
	default:
		fifo_mode = 0;
		/* fall through */
	case 0:
		udc->fifo_cfg = NULL;
		n = 0;
		break;
	case 1:
		udc->fifo_cfg = mode_1_cfg;
		n = ARRAY_SIZE(mode_1_cfg);
		break;
	case 2:
		udc->fifo_cfg = mode_2_cfg;
		n = ARRAY_SIZE(mode_2_cfg);
		break;
	case 3:
		udc->fifo_cfg = mode_3_cfg;
		n = ARRAY_SIZE(mode_3_cfg);
		break;
	case 4:
		udc->fifo_cfg = mode_4_cfg;
		n = ARRAY_SIZE(mode_4_cfg);
		break;
	}
	DBG(DBG_HW, "Setup fifo_mode %d\n", fifo_mode);

	return n;
}