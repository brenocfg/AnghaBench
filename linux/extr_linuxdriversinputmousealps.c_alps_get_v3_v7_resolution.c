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
struct psmouse {struct alps_data* private; } ;
struct alps_data {int x_res; int x_max; int y_res; int y_max; } ;

/* Variables and functions */
 int alps_command_mode_read_reg (struct psmouse*,int) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,int,int,int,int,int,int,int,int) ; 

__attribute__((used)) static int alps_get_v3_v7_resolution(struct psmouse *psmouse, int reg_pitch)
{
	int reg, x_pitch, y_pitch, x_electrode, y_electrode, x_phys, y_phys;
	struct alps_data *priv = psmouse->private;

	reg = alps_command_mode_read_reg(psmouse, reg_pitch);
	if (reg < 0)
		return reg;

	x_pitch = (char)(reg << 4) >> 4; /* sign extend lower 4 bits */
	x_pitch = 50 + 2 * x_pitch; /* In 0.1 mm units */

	y_pitch = (char)reg >> 4; /* sign extend upper 4 bits */
	y_pitch = 36 + 2 * y_pitch; /* In 0.1 mm units */

	reg = alps_command_mode_read_reg(psmouse, reg_pitch + 1);
	if (reg < 0)
		return reg;

	x_electrode = (char)(reg << 4) >> 4; /* sign extend lower 4 bits */
	x_electrode = 17 + x_electrode;

	y_electrode = (char)reg >> 4; /* sign extend upper 4 bits */
	y_electrode = 13 + y_electrode;

	x_phys = x_pitch * (x_electrode - 1); /* In 0.1 mm units */
	y_phys = y_pitch * (y_electrode - 1); /* In 0.1 mm units */

	priv->x_res = priv->x_max * 10 / x_phys; /* units / mm */
	priv->y_res = priv->y_max * 10 / y_phys; /* units / mm */

	psmouse_dbg(psmouse,
		    "pitch %dx%d num-electrodes %dx%d physical size %dx%d mm res %dx%d\n",
		    x_pitch, y_pitch, x_electrode, y_electrode,
		    x_phys / 10, y_phys / 10, priv->x_res, priv->y_res);

	return 0;
}