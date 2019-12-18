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
struct isl6423_dev {struct isl6423_config* config; } ;
struct isl6423_config {scalar_t__ mod_extern; } ;
struct dvb_frontend {scalar_t__ sec_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ERROR ; 
 int /*<<< orphan*/  dprintk (int /*<<< orphan*/ ,int,char*,int) ; 
 int isl6423_write (struct isl6423_dev*,int) ; 

__attribute__((used)) static int isl6423_set_modulation(struct dvb_frontend *fe)
{
	struct isl6423_dev *isl6423		= (struct isl6423_dev *) fe->sec_priv;
	const struct isl6423_config *config	= isl6423->config;
	int err = 0;
	u8 reg_2 = 0;

	reg_2 = 0x01 << 5;

	if (config->mod_extern)
		reg_2 |= (1 << 3);
	else
		reg_2 |= (1 << 4);

	err = isl6423_write(isl6423, reg_2);
	if (err < 0)
		goto exit;
	return 0;

exit:
	dprintk(FE_ERROR, 1, "I/O error <%d>", err);
	return err;
}