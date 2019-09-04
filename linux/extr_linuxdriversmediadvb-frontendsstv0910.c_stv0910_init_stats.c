#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int len; TYPE_8__* stat; } ;
struct TYPE_16__ {int len; TYPE_6__* stat; } ;
struct TYPE_14__ {int len; TYPE_4__* stat; } ;
struct TYPE_12__ {int len; TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_9__ pre_bit_count; TYPE_7__ pre_bit_error; TYPE_5__ cnr; TYPE_3__ strength; } ;
struct TYPE_10__ {struct dtv_frontend_properties dtv_property_cache; } ;
struct stv {TYPE_1__ fe; } ;
struct TYPE_17__ {void* scale; } ;
struct TYPE_15__ {void* scale; } ;
struct TYPE_13__ {void* scale; } ;
struct TYPE_11__ {void* scale; } ;

/* Variables and functions */
 void* FE_SCALE_NOT_AVAILABLE ; 

__attribute__((used)) static void stv0910_init_stats(struct stv *state)
{
	struct dtv_frontend_properties *p = &state->fe.dtv_property_cache;

	p->strength.len = 1;
	p->strength.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->cnr.len = 1;
	p->cnr.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_error.len = 1;
	p->pre_bit_error.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
	p->pre_bit_count.len = 1;
	p->pre_bit_count.stat[0].scale = FE_SCALE_NOT_AVAILABLE;
}