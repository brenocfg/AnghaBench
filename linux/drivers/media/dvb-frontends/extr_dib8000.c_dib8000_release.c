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
typedef  size_t u8 ;
struct dvb_frontend {struct dib8000_state* demodulator_priv; } ;
struct dib8000_state {struct dib8000_state** fe; int /*<<< orphan*/  dib8096p_tuner_adap; int /*<<< orphan*/  i2c_master; } ;

/* Variables and functions */
 size_t MAX_NUMBER_OF_FRONTENDS ; 
 int /*<<< orphan*/  dibx000_exit_i2c_master (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dvb_frontend_detach (struct dib8000_state*) ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dib8000_state*) ; 

__attribute__((used)) static void dib8000_release(struct dvb_frontend *fe)
{
	struct dib8000_state *st = fe->demodulator_priv;
	u8 index_frontend;

	for (index_frontend = 1; (index_frontend < MAX_NUMBER_OF_FRONTENDS) && (st->fe[index_frontend] != NULL); index_frontend++)
		dvb_frontend_detach(st->fe[index_frontend]);

	dibx000_exit_i2c_master(&st->i2c_master);
	i2c_del_adapter(&st->dib8096p_tuner_adap);
	kfree(st->fe[0]);
	kfree(st);
}