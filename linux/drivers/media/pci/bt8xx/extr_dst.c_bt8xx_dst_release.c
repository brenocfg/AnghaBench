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
struct dvb_frontend {struct dst_state* demodulator_priv; } ;
struct dst_state {scalar_t__ dst_ca; } ;

/* Variables and functions */
 int /*<<< orphan*/  dst_ca_attach ; 
 int /*<<< orphan*/  dvb_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct dst_state*) ; 
 int /*<<< orphan*/  symbol_put (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bt8xx_dst_release(struct dvb_frontend *fe)
{
	struct dst_state *state = fe->demodulator_priv;
	if (state->dst_ca) {
		dvb_unregister_device(state->dst_ca);
#ifdef CONFIG_MEDIA_ATTACH
		symbol_put(dst_ca_attach);
#endif
	}
	kfree(state);
}