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
typedef  int /*<<< orphan*/  u8 ;
struct i2c_adapter {int dummy; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LNBP21_ISEL ; 
 struct dvb_frontend* lnbx2x_attach (struct dvb_frontend*,struct i2c_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

struct dvb_frontend *lnbp21_attach(struct dvb_frontend *fe,
				struct i2c_adapter *i2c, u8 override_set,
				u8 override_clear)
{
	return lnbx2x_attach(fe, i2c, override_set, override_clear,
							0x08, LNBP21_ISEL);
}