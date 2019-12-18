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
struct gp8psk_fe_state {int /*<<< orphan*/  priv; TYPE_1__* ops; } ;
struct dvb_frontend {struct gp8psk_fe_state* demodulator_priv; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* in ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GET_8PSK_CONFIG ; 
 int bmDCtuned ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static int gp8psk_tuned_to_DCII(struct dvb_frontend *fe)
{
	struct gp8psk_fe_state *st = fe->demodulator_priv;
	u8 status;

	st->ops->in(st->priv, GET_8PSK_CONFIG, 0, 0, &status, 1);
	return status & bmDCtuned;
}