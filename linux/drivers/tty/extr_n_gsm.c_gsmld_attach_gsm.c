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
struct tty_struct {int dummy; } ;
struct gsm_mux {int /*<<< orphan*/  tty; int /*<<< orphan*/  output; } ;

/* Variables and functions */
 int NUM_DLCI ; 
 int gsm_activate_mux (struct gsm_mux*) ; 
 int /*<<< orphan*/  gsm_tty_driver ; 
 int /*<<< orphan*/  gsmld_output ; 
 unsigned int mux_num_to_base (struct gsm_mux*) ; 
 int /*<<< orphan*/  tty_kref_get (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_kref_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_register_device (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gsmld_attach_gsm(struct tty_struct *tty, struct gsm_mux *gsm)
{
	unsigned int base;
	int ret, i;

	gsm->tty = tty_kref_get(tty);
	gsm->output = gsmld_output;
	ret =  gsm_activate_mux(gsm);
	if (ret != 0)
		tty_kref_put(gsm->tty);
	else {
		/* Don't register device 0 - this is the control channel and not
		   a usable tty interface */
		base = mux_num_to_base(gsm); /* Base for this MUX */
		for (i = 1; i < NUM_DLCI; i++)
			tty_register_device(gsm_tty_driver, base + i, NULL);
	}
	return ret;
}