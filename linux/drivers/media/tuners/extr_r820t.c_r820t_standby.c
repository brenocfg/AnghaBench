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
struct r820t_priv {int type; int /*<<< orphan*/  init_done; } ;

/* Variables and functions */
 int r820t_write_reg (struct r820t_priv*,int,int) ; 

__attribute__((used)) static int r820t_standby(struct r820t_priv *priv)
{
	int rc;

	/* If device was not initialized yet, don't need to standby */
	if (!priv->init_done)
		return 0;

	rc = r820t_write_reg(priv, 0x06, 0xb1);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x05, 0x03);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x07, 0x3a);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x08, 0x40);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x09, 0xc0);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x0a, 0x36);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x0c, 0x35);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x0f, 0x68);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x11, 0x03);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x17, 0xf4);
	if (rc < 0)
		return rc;
	rc = r820t_write_reg(priv, 0x19, 0x0c);

	/* Force initial calibration */
	priv->type = -1;

	return rc;
}