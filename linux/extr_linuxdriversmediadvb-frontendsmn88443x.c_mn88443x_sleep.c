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
struct mn88443x_priv {int dummy; } ;
struct dvb_frontend {struct mn88443x_priv* demodulator_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  mn88443x_s_sleep (struct mn88443x_priv*) ; 
 int /*<<< orphan*/  mn88443x_t_sleep (struct mn88443x_priv*) ; 

__attribute__((used)) static int mn88443x_sleep(struct dvb_frontend *fe)
{
	struct mn88443x_priv *chip = fe->demodulator_priv;

	mn88443x_s_sleep(chip);
	mn88443x_t_sleep(chip);

	return 0;
}