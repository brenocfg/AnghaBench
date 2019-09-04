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
struct ngene_channel {int demod_type; } ;

/* Variables and functions */
#define  DEMOD_TYPE_DRXK 135 
#define  DEMOD_TYPE_SONY_C2T2 134 
#define  DEMOD_TYPE_SONY_C2T2I 133 
#define  DEMOD_TYPE_SONY_CT2 132 
#define  DEMOD_TYPE_SONY_ISDBT 131 
#define  DEMOD_TYPE_STV0367 130 
#define  DEMOD_TYPE_STV090X 129 
#define  DEMOD_TYPE_STV0910 128 
 int EINVAL ; 
 int tuner_attach_stv6110 (struct ngene_channel*) ; 
 int tuner_attach_stv6111 (struct ngene_channel*) ; 
 int tuner_attach_tda18212 (struct ngene_channel*,int) ; 
 int tuner_attach_tda18271 (struct ngene_channel*) ; 

__attribute__((used)) static int tuner_attach_probe(struct ngene_channel *chan)
{
	switch (chan->demod_type) {
	case DEMOD_TYPE_STV090X:
		return tuner_attach_stv6110(chan);
	case DEMOD_TYPE_DRXK:
		return tuner_attach_tda18271(chan);
	case DEMOD_TYPE_STV0367:
	case DEMOD_TYPE_SONY_CT2:
	case DEMOD_TYPE_SONY_ISDBT:
	case DEMOD_TYPE_SONY_C2T2:
	case DEMOD_TYPE_SONY_C2T2I:
		return tuner_attach_tda18212(chan, chan->demod_type);
	case DEMOD_TYPE_STV0910:
		return tuner_attach_stv6111(chan);
	}

	return -EINVAL;
}