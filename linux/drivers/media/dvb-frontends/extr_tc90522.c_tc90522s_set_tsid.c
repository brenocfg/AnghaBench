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
struct reg_val {int member_0; int member_1; int val; } ;
struct TYPE_2__ {int stream_id; } ;
struct dvb_frontend {int /*<<< orphan*/  demodulator_priv; TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct reg_val*) ; 
 int reg_write (int /*<<< orphan*/ ,struct reg_val*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tc90522s_set_tsid(struct dvb_frontend *fe)
{
	struct reg_val set_tsid[] = {
		{ 0x8f, 00 },
		{ 0x90, 00 }
	};

	set_tsid[0].val = (fe->dtv_property_cache.stream_id & 0xff00) >> 8;
	set_tsid[1].val = fe->dtv_property_cache.stream_id & 0xff;
	return reg_write(fe->demodulator_priv, set_tsid, ARRAY_SIZE(set_tsid));
}