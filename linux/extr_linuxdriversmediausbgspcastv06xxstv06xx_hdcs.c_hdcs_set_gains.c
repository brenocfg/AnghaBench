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
struct sd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDCS_ERECPGA ; 
 int hdcs_reg_write_seq (struct sd*,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int hdcs_set_gains(struct sd *sd, u8 g)
{
	int err;
	u8 gains[4];

	/* the voltage gain Av = (1 + 19 * val / 127) * (1 + bit7) */
	if (g > 127)
		g = 0x80 | (g / 2);

	gains[0] = g;
	gains[1] = g;
	gains[2] = g;
	gains[3] = g;

	err = hdcs_reg_write_seq(sd, HDCS_ERECPGA, gains, 4);
	return err;
}