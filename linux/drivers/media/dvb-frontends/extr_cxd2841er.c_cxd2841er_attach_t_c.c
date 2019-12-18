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
struct i2c_adapter {int dummy; } ;
struct dvb_frontend {int dummy; } ;
struct cxd2841er_config {int dummy; } ;

/* Variables and functions */
 struct dvb_frontend* cxd2841er_attach (struct cxd2841er_config*,struct i2c_adapter*,int /*<<< orphan*/ ) ; 

struct dvb_frontend *cxd2841er_attach_t_c(struct cxd2841er_config *cfg,
					struct i2c_adapter *i2c)
{
	return cxd2841er_attach(cfg, i2c, 0);
}