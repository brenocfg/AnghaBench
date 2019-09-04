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
typedef  int u32 ;
struct TYPE_2__ {int bandwidth_hz; } ;
struct dvb_frontend {TYPE_1__ dtv_property_cache; } ;

/* Variables and functions */

__attribute__((used)) static void thomson_dtt7520x_bw(struct dvb_frontend *fe, u8 *buf)
{
	u32 bw = fe->dtv_property_cache.bandwidth_hz;
	if (bw == 8000000)
		buf[3] ^= 0x10;
}