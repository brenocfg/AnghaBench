#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct reg_val {int reg; int val; } ;
struct TYPE_2__ {int isdbt_layer_enabled; } ;
struct dvb_frontend {int /*<<< orphan*/  demodulator_priv; TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
 int reg_write (int /*<<< orphan*/ ,struct reg_val*,int) ; 

__attribute__((used)) static int tc90522t_set_layers(struct dvb_frontend *fe)
{
	struct reg_val rv;
	u8 laysel;

	laysel = ~fe->dtv_property_cache.isdbt_layer_enabled & 0x07;
	laysel = (laysel & 0x01) << 2 | (laysel & 0x02) | (laysel & 0x04) >> 2;
	rv.reg = 0x71;
	rv.val = laysel;
	return reg_write(fe->demodulator_priv, &rv, 1);
}