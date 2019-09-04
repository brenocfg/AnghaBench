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
struct nct6775_data {int sioreg; int sio_reg_enable; int kind; int has_fan; int has_fan_min; int has_pwm; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  DMI_BOARD_NAME ; 
 int /*<<< orphan*/  DMI_BOARD_VENDOR ; 
 int /*<<< orphan*/  NCT6775_LD_12 ; 
 int /*<<< orphan*/  NCT6775_LD_HWM ; 
 int SIO_REG_ENABLE ; 
 char* dmi_get_system_info (int /*<<< orphan*/ ) ; 
 int nct6106 ; 
 int nct6775 ; 
 int nct6776 ; 
#define  nct6791 132 
#define  nct6792 131 
#define  nct6793 130 
#define  nct6795 129 
#define  nct6796 128 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int superio_inb (int,int) ; 
 int /*<<< orphan*/  superio_outb (int,int,int) ; 
 int /*<<< orphan*/  superio_select (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
nct6775_check_fan_inputs(struct nct6775_data *data)
{
	bool fan3pin = false, fan4pin = false, fan4min = false;
	bool fan5pin = false, fan6pin = false, fan7pin = false;
	bool pwm3pin = false, pwm4pin = false, pwm5pin = false;
	bool pwm6pin = false, pwm7pin = false;
	int sioreg = data->sioreg;
	int regval;

	/* Store SIO_REG_ENABLE for use during resume */
	superio_select(sioreg, NCT6775_LD_HWM);
	data->sio_reg_enable = superio_inb(sioreg, SIO_REG_ENABLE);

	/* fan4 and fan5 share some pins with the GPIO and serial flash */
	if (data->kind == nct6775) {
		regval = superio_inb(sioreg, 0x2c);

		fan3pin = regval & BIT(6);
		pwm3pin = regval & BIT(7);

		/* On NCT6775, fan4 shares pins with the fdc interface */
		fan4pin = !(superio_inb(sioreg, 0x2A) & 0x80);
	} else if (data->kind == nct6776) {
		bool gpok = superio_inb(sioreg, 0x27) & 0x80;
		const char *board_vendor, *board_name;

		board_vendor = dmi_get_system_info(DMI_BOARD_VENDOR);
		board_name = dmi_get_system_info(DMI_BOARD_NAME);

		if (board_name && board_vendor &&
		    !strcmp(board_vendor, "ASRock")) {
			/*
			 * Auxiliary fan monitoring is not enabled on ASRock
			 * Z77 Pro4-M if booted in UEFI Ultra-FastBoot mode.
			 * Observed with BIOS version 2.00.
			 */
			if (!strcmp(board_name, "Z77 Pro4-M")) {
				if ((data->sio_reg_enable & 0xe0) != 0xe0) {
					data->sio_reg_enable |= 0xe0;
					superio_outb(sioreg, SIO_REG_ENABLE,
						     data->sio_reg_enable);
				}
			}
		}

		if (data->sio_reg_enable & 0x80)
			fan3pin = gpok;
		else
			fan3pin = !(superio_inb(sioreg, 0x24) & 0x40);

		if (data->sio_reg_enable & 0x40)
			fan4pin = gpok;
		else
			fan4pin = superio_inb(sioreg, 0x1C) & 0x01;

		if (data->sio_reg_enable & 0x20)
			fan5pin = gpok;
		else
			fan5pin = superio_inb(sioreg, 0x1C) & 0x02;

		fan4min = fan4pin;
		pwm3pin = fan3pin;
	} else if (data->kind == nct6106) {
		regval = superio_inb(sioreg, 0x24);
		fan3pin = !(regval & 0x80);
		pwm3pin = regval & 0x08;
	} else {
		/* NCT6779D, NCT6791D, NCT6792D, NCT6793D, NCT6795D, NCT6796D */
		int regval_1b, regval_2a, regval_2f;
		bool dsw_en;

		regval = superio_inb(sioreg, 0x1c);

		fan3pin = !(regval & BIT(5));
		fan4pin = !(regval & BIT(6));
		fan5pin = !(regval & BIT(7));

		pwm3pin = !(regval & BIT(0));
		pwm4pin = !(regval & BIT(1));
		pwm5pin = !(regval & BIT(2));

		regval = superio_inb(sioreg, 0x2d);
		switch (data->kind) {
		case nct6791:
		case nct6792:
			fan6pin = regval & BIT(1);
			pwm6pin = regval & BIT(0);
			break;
		case nct6793:
		case nct6795:
		case nct6796:
			regval_1b = superio_inb(sioreg, 0x1b);
			regval_2a = superio_inb(sioreg, 0x2a);
			regval_2f = superio_inb(sioreg, 0x2f);
			dsw_en = regval_2f & BIT(3);

			if (!pwm5pin)
				pwm5pin = regval & BIT(7);

			if (!fan5pin)
				fan5pin = regval_1b & BIT(5);

			superio_select(sioreg, NCT6775_LD_12);
			if (data->kind != nct6796) {
				int regval_eb = superio_inb(sioreg, 0xeb);

				if (!dsw_en) {
					fan6pin = regval & BIT(1);
					pwm6pin = regval & BIT(0);
				}

				if (!fan5pin)
					fan5pin = regval_eb & BIT(5);
				if (!pwm5pin)
					pwm5pin = (regval_eb & BIT(4)) &&
						!(regval_2a & BIT(0));
				if (!fan6pin)
					fan6pin = regval_eb & BIT(3);
				if (!pwm6pin)
					pwm6pin = regval_eb & BIT(2);
			}

			if (data->kind == nct6795 || data->kind == nct6796) {
				int regval_ed = superio_inb(sioreg, 0xed);

				if (!fan6pin)
					fan6pin = (regval_2a & BIT(4)) &&
					  (!dsw_en ||
					   (dsw_en && (regval_ed & BIT(4))));
				if (!pwm6pin)
					pwm6pin = (regval_2a & BIT(3)) &&
					  (regval_ed & BIT(2));
			}

			if (data->kind == nct6796) {
				int regval_1d = superio_inb(sioreg, 0x1d);
				int regval_2b = superio_inb(sioreg, 0x2b);

				fan7pin = !(regval_2b & BIT(2));
				pwm7pin = !(regval_1d & (BIT(2) | BIT(3)));
			}

			break;
		default:	/* NCT6779D */
			break;
		}

		fan4min = fan4pin;
	}

	/* fan 1 and 2 (0x03) are always present */
	data->has_fan = 0x03 | (fan3pin << 2) | (fan4pin << 3) |
		(fan5pin << 4) | (fan6pin << 5) | (fan7pin << 6);
	data->has_fan_min = 0x03 | (fan3pin << 2) | (fan4min << 3) |
		(fan5pin << 4) | (fan6pin << 5) | (fan7pin << 6);
	data->has_pwm = 0x03 | (pwm3pin << 2) | (pwm4pin << 3) |
		(pwm5pin << 4) | (pwm6pin << 5) | (pwm7pin << 6);
}