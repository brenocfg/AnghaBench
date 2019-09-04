#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct mxl {TYPE_1__* base; int /*<<< orphan*/  demod; } ;
struct TYPE_6__ {TYPE_2__* stat; } ;
struct dtv_frontend_properties {TYPE_3__ cnr; } ;
struct dvb_frontend {struct dtv_frontend_properties dtv_property_cache; struct mxl* demodulator_priv; } ;
typedef  int s16 ;
struct TYPE_5__ {int svalue; int /*<<< orphan*/  scale; } ;
struct TYPE_4__ {int /*<<< orphan*/  status_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  FE_SCALE_DECIBEL ; 
 int /*<<< orphan*/  HYDRA_DEMOD_STATUS_LOCK (struct mxl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HYDRA_DEMOD_STATUS_UNLOCK (struct mxl*,int /*<<< orphan*/ ) ; 
 scalar_t__ HYDRA_DMD_SNR_ADDR_OFFSET ; 
 scalar_t__ HYDRA_DMD_STATUS_OFFSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_register (struct mxl*,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static int read_snr(struct dvb_frontend *fe)
{
	struct mxl *state = fe->demodulator_priv;
	int stat;
	u32 reg_data = 0;
	struct dtv_frontend_properties *p = &fe->dtv_property_cache;

	mutex_lock(&state->base->status_lock);
	HYDRA_DEMOD_STATUS_LOCK(state, state->demod);
	stat = read_register(state, (HYDRA_DMD_SNR_ADDR_OFFSET +
				     HYDRA_DMD_STATUS_OFFSET(state->demod)),
			     &reg_data);
	HYDRA_DEMOD_STATUS_UNLOCK(state, state->demod);
	mutex_unlock(&state->base->status_lock);

	p->cnr.stat[0].scale = FE_SCALE_DECIBEL;
	p->cnr.stat[0].svalue = (s16)reg_data * 10;

	return stat;
}