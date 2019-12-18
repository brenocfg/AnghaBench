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
struct i2c_adapter {int /*<<< orphan*/  dev; } ;
struct fc0011_config {int dummy; } ;
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static inline
struct dvb_frontend *fc0011_attach(struct dvb_frontend *fe,
				   struct i2c_adapter *i2c,
				   const struct fc0011_config *config)
{
	dev_err(&i2c->dev, "fc0011 driver disabled in Kconfig\n");
	return NULL;
}