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
struct vin_coeff {unsigned short xs_value; int /*<<< orphan*/ * coeff_set; } ;
struct rvin_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct vin_coeff*) ; 
 int /*<<< orphan*/  VNC1A_REG ; 
 int /*<<< orphan*/  VNC1B_REG ; 
 int /*<<< orphan*/  VNC1C_REG ; 
 int /*<<< orphan*/  VNC2A_REG ; 
 int /*<<< orphan*/  VNC2B_REG ; 
 int /*<<< orphan*/  VNC2C_REG ; 
 int /*<<< orphan*/  VNC3A_REG ; 
 int /*<<< orphan*/  VNC3B_REG ; 
 int /*<<< orphan*/  VNC3C_REG ; 
 int /*<<< orphan*/  VNC4A_REG ; 
 int /*<<< orphan*/  VNC4B_REG ; 
 int /*<<< orphan*/  VNC4C_REG ; 
 int /*<<< orphan*/  VNC5A_REG ; 
 int /*<<< orphan*/  VNC5B_REG ; 
 int /*<<< orphan*/  VNC5C_REG ; 
 int /*<<< orphan*/  VNC6A_REG ; 
 int /*<<< orphan*/  VNC6B_REG ; 
 int /*<<< orphan*/  VNC6C_REG ; 
 int /*<<< orphan*/  VNC7A_REG ; 
 int /*<<< orphan*/  VNC7B_REG ; 
 int /*<<< orphan*/  VNC7C_REG ; 
 int /*<<< orphan*/  VNC8A_REG ; 
 int /*<<< orphan*/  VNC8B_REG ; 
 int /*<<< orphan*/  VNC8C_REG ; 
 int /*<<< orphan*/  rvin_write (struct rvin_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vin_coeff* vin_coeff_set ; 

__attribute__((used)) static void rvin_set_coeff(struct rvin_dev *vin, unsigned short xs)
{
	int i;
	const struct vin_coeff *p_prev_set = NULL;
	const struct vin_coeff *p_set = NULL;

	/* Look for suitable coefficient values */
	for (i = 0; i < ARRAY_SIZE(vin_coeff_set); i++) {
		p_prev_set = p_set;
		p_set = &vin_coeff_set[i];

		if (xs < p_set->xs_value)
			break;
	}

	/* Use previous value if its XS value is closer */
	if (p_prev_set &&
	    xs - p_prev_set->xs_value < p_set->xs_value - xs)
		p_set = p_prev_set;

	/* Set coefficient registers */
	rvin_write(vin, p_set->coeff_set[0], VNC1A_REG);
	rvin_write(vin, p_set->coeff_set[1], VNC1B_REG);
	rvin_write(vin, p_set->coeff_set[2], VNC1C_REG);

	rvin_write(vin, p_set->coeff_set[3], VNC2A_REG);
	rvin_write(vin, p_set->coeff_set[4], VNC2B_REG);
	rvin_write(vin, p_set->coeff_set[5], VNC2C_REG);

	rvin_write(vin, p_set->coeff_set[6], VNC3A_REG);
	rvin_write(vin, p_set->coeff_set[7], VNC3B_REG);
	rvin_write(vin, p_set->coeff_set[8], VNC3C_REG);

	rvin_write(vin, p_set->coeff_set[9], VNC4A_REG);
	rvin_write(vin, p_set->coeff_set[10], VNC4B_REG);
	rvin_write(vin, p_set->coeff_set[11], VNC4C_REG);

	rvin_write(vin, p_set->coeff_set[12], VNC5A_REG);
	rvin_write(vin, p_set->coeff_set[13], VNC5B_REG);
	rvin_write(vin, p_set->coeff_set[14], VNC5C_REG);

	rvin_write(vin, p_set->coeff_set[15], VNC6A_REG);
	rvin_write(vin, p_set->coeff_set[16], VNC6B_REG);
	rvin_write(vin, p_set->coeff_set[17], VNC6C_REG);

	rvin_write(vin, p_set->coeff_set[18], VNC7A_REG);
	rvin_write(vin, p_set->coeff_set[19], VNC7B_REG);
	rvin_write(vin, p_set->coeff_set[20], VNC7C_REG);

	rvin_write(vin, p_set->coeff_set[21], VNC8A_REG);
	rvin_write(vin, p_set->coeff_set[22], VNC8B_REG);
	rvin_write(vin, p_set->coeff_set[23], VNC8C_REG);
}