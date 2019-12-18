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
struct isl6423_dev {int reg_3; struct isl6423_config* config; } ;
struct isl6423_config {int current_max; int curlim; } ;
struct dvb_frontend {scalar_t__ sec_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ERROR ; 
#define  SEC_CURRENT_275m 133 
#define  SEC_CURRENT_515m 132 
#define  SEC_CURRENT_635m 131 
#define  SEC_CURRENT_800m 130 
#define  SEC_CURRENT_LIM_OFF 129 
#define  SEC_CURRENT_LIM_ON 128 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 int isl6423_write (struct isl6423_dev*,int) ; 

__attribute__((used)) static int isl6423_set_current(struct dvb_frontend *fe)
{
	struct isl6423_dev *isl6423		= (struct isl6423_dev *) fe->sec_priv;
	u8 reg_3 = isl6423->reg_3;
	const struct isl6423_config *config	= isl6423->config;
	int err = 0;

	switch (config->current_max) {
	case SEC_CURRENT_275m:
		/* 275mA */
		/* ISELH = 0, ISELL = 0 */
		reg_3 &= ~0x3;
		break;

	case SEC_CURRENT_515m:
		/* 515mA */
		/* ISELH = 0, ISELL = 1 */
		reg_3 &= ~0x2;
		reg_3 |=  0x1;
		break;

	case SEC_CURRENT_635m:
		/* 635mA */
		/* ISELH = 1, ISELL = 0 */
		reg_3 &= ~0x1;
		reg_3 |=  0x2;
		break;

	case SEC_CURRENT_800m:
		/* 800mA */
		/* ISELH = 1, ISELL = 1 */
		reg_3 |= 0x3;
		break;
	}

	err = isl6423_write(isl6423, reg_3);
	if (err < 0)
		goto exit;

	switch (config->curlim) {
	case SEC_CURRENT_LIM_ON:
		/* DCL = 0 */
		reg_3 &= ~0x10;
		break;

	case SEC_CURRENT_LIM_OFF:
		/* DCL = 1 */
		reg_3 |= 0x10;
		break;
	}

	err = isl6423_write(isl6423, reg_3);
	if (err < 0)
		goto exit;

	isl6423->reg_3 = reg_3;

	return 0;
exit:
	dprintk(FE_ERROR, 1, "I/O error <%d>", err);
	return err;
}