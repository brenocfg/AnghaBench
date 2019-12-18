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
struct isl6423_dev {int reg_3; int reg_4; } ;
struct dvb_frontend {scalar_t__ sec_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 int isl6423_write (struct isl6423_dev*,int) ; 

__attribute__((used)) static int isl6423_voltage_boost(struct dvb_frontend *fe, long arg)
{
	struct isl6423_dev *isl6423 = (struct isl6423_dev *) fe->sec_priv;
	u8 reg_3 = isl6423->reg_3;
	u8 reg_4 = isl6423->reg_4;
	int err = 0;

	if (arg) {
		/* EN = 1, VSPEN = 1, VBOT = 1 */
		reg_4 |= (1 << 4);
		reg_4 |= 0x1;
		reg_3 |= (1 << 3);
	} else {
		/* EN = 1, VSPEN = 1, VBOT = 0 */
		reg_4 |= (1 << 4);
		reg_4 &= ~0x1;
		reg_3 |= (1 << 3);
	}
	err = isl6423_write(isl6423, reg_3);
	if (err < 0)
		goto exit;

	err = isl6423_write(isl6423, reg_4);
	if (err < 0)
		goto exit;

	isl6423->reg_3 = reg_3;
	isl6423->reg_4 = reg_4;

	return 0;
exit:
	dprintk(FE_ERROR, 1, "I/O error <%d>", err);
	return err;
}