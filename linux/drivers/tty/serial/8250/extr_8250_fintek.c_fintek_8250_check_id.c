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
typedef  int u16 ;
struct fintek_8250 {int pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHIP_ID1 ; 
 int /*<<< orphan*/  CHIP_ID2 ; 
#define  CHIP_ID_F81216 132 
#define  CHIP_ID_F81216AD 131 
#define  CHIP_ID_F81216H 130 
#define  CHIP_ID_F81865 129 
#define  CHIP_ID_F81866 128 
 int ENODEV ; 
 int /*<<< orphan*/  VENDOR_ID1 ; 
 int VENDOR_ID1_VAL ; 
 int /*<<< orphan*/  VENDOR_ID2 ; 
 int VENDOR_ID2_VAL ; 
 int sio_read_reg (struct fintek_8250*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fintek_8250_check_id(struct fintek_8250 *pdata)
{
	u16 chip;

	if (sio_read_reg(pdata, VENDOR_ID1) != VENDOR_ID1_VAL)
		return -ENODEV;

	if (sio_read_reg(pdata, VENDOR_ID2) != VENDOR_ID2_VAL)
		return -ENODEV;

	chip = sio_read_reg(pdata, CHIP_ID1);
	chip |= sio_read_reg(pdata, CHIP_ID2) << 8;

	switch (chip) {
	case CHIP_ID_F81865:
	case CHIP_ID_F81866:
	case CHIP_ID_F81216AD:
	case CHIP_ID_F81216H:
	case CHIP_ID_F81216:
		break;
	default:
		return -ENODEV;
	}

	pdata->pid = chip;
	return 0;
}