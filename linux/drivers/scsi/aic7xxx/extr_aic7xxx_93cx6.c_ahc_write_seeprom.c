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
typedef  int uint8_t ;
typedef  int uint16_t ;
typedef  int u_int ;
struct seeprom_descriptor {scalar_t__ sd_chip; int sd_MS; int sd_CS; int sd_DO; int sd_CK; int sd_DI; int /*<<< orphan*/  sd_RDY; } ;
struct seeprom_cmd {int dummy; } ;

/* Variables and functions */
 scalar_t__ C46 ; 
 scalar_t__ C56_66 ; 
 int /*<<< orphan*/  CLOCK_PULSE (struct seeprom_descriptor*,int /*<<< orphan*/ ) ; 
 int SEEPROM_DATA_INB (struct seeprom_descriptor*) ; 
 int /*<<< orphan*/  SEEPROM_OUTB (struct seeprom_descriptor*,int) ; 
 int /*<<< orphan*/  printk (char*,scalar_t__) ; 
 int /*<<< orphan*/  reset_seeprom (struct seeprom_descriptor*) ; 
 struct seeprom_cmd seeprom_ewds ; 
 struct seeprom_cmd seeprom_ewen ; 
 struct seeprom_cmd seeprom_long_ewds ; 
 struct seeprom_cmd seeprom_long_ewen ; 
 struct seeprom_cmd const seeprom_write ; 
 int /*<<< orphan*/  send_seeprom_cmd (struct seeprom_descriptor*,struct seeprom_cmd const*) ; 

int
ahc_write_seeprom(struct seeprom_descriptor *sd, uint16_t *buf,
		  u_int start_addr, u_int count)
{
	const struct seeprom_cmd *ewen, *ewds;
	uint16_t v;
	uint8_t temp;
	int i, k;

	/* Place the chip into write-enable mode */
	if (sd->sd_chip == C46) {
		ewen = &seeprom_ewen;
		ewds = &seeprom_ewds;
	} else if (sd->sd_chip == C56_66) {
		ewen = &seeprom_long_ewen;
		ewds = &seeprom_long_ewds;
	} else {
		printk("ahc_write_seeprom: unsupported seeprom type %d\n",
		       sd->sd_chip);
		return (0);
	}

	send_seeprom_cmd(sd, ewen);
	reset_seeprom(sd);

	/* Write all requested data out to the seeprom. */
	temp = sd->sd_MS ^ sd->sd_CS;
	for (k = start_addr; k < count + start_addr; k++) {
		/* Send the write command */
		send_seeprom_cmd(sd, &seeprom_write);

		/* Send the 6 or 8 bit address (MSB first). */
		for (i = (sd->sd_chip - 1); i >= 0; i--) {
			if ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
			if ((k & (1 << i)) != 0)
				temp ^= sd->sd_DO;
		}

		/* Write the 16 bit value, MSB first */
		v = buf[k - start_addr];
		for (i = 15; i >= 0; i--) {
			if ((v & (1 << i)) != 0)
				temp ^= sd->sd_DO;
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
			if ((v & (1 << i)) != 0)
				temp ^= sd->sd_DO;
		}

		/* Wait for the chip to complete the write */
		temp = sd->sd_MS;
		SEEPROM_OUTB(sd, temp);
		CLOCK_PULSE(sd, sd->sd_RDY);
		temp = sd->sd_MS ^ sd->sd_CS;
		do {
			SEEPROM_OUTB(sd, temp);
			CLOCK_PULSE(sd, sd->sd_RDY);
			SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
			CLOCK_PULSE(sd, sd->sd_RDY);
		} while ((SEEPROM_DATA_INB(sd) & sd->sd_DI) == 0);

		reset_seeprom(sd);
	}

	/* Put the chip back into write-protect mode */
	send_seeprom_cmd(sd, ewds);
	reset_seeprom(sd);

	return (1);
}