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
struct seeprom_descriptor {int sd_MS; int sd_CK; int /*<<< orphan*/  sd_RDY; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_PULSE (struct seeprom_descriptor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEEPROM_OUTB (struct seeprom_descriptor*,int) ; 

__attribute__((used)) static void
reset_seeprom(struct seeprom_descriptor *sd)
{
	uint8_t temp;

	temp = sd->sd_MS;
	SEEPROM_OUTB(sd, temp);
	CLOCK_PULSE(sd, sd->sd_RDY);
	SEEPROM_OUTB(sd, temp ^ sd->sd_CK);
	CLOCK_PULSE(sd, sd->sd_RDY);
	SEEPROM_OUTB(sd, temp);
	CLOCK_PULSE(sd, sd->sd_RDY);
}