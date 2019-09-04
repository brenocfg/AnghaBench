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
struct pluto {int i2cbug; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_SLCS ; 
 int /*<<< orphan*/  SLCS_SCL ; 
 int /*<<< orphan*/  pluto_rw (struct pluto*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pluto_setsda (struct pluto*,int) ; 

__attribute__((used)) static void pluto_setscl(void *data, int state)
{
	struct pluto *pluto = data;

	if (state)
		pluto_rw(pluto, REG_SLCS, SLCS_SCL, SLCS_SCL);
	else
		pluto_rw(pluto, REG_SLCS, SLCS_SCL, 0);

	/* try to detect i2c_inb() to workaround hardware bug:
	 * reset SDA to high after SCL has been set to low */
	if ((state) && (pluto->i2cbug == 0)) {
		pluto->i2cbug = 1;
	} else {
		if ((!state) && (pluto->i2cbug == 1))
			pluto_setsda(pluto, 1);
		pluto->i2cbug = 0;
	}
}