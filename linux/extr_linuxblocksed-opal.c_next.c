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
struct opal_step {int (* fn ) (struct opal_dev*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  data; } ;
struct opal_dev {struct opal_step* steps; } ;

/* Variables and functions */
 int /*<<< orphan*/  end_opal_session_error (struct opal_dev*) ; 
 int /*<<< orphan*/  opal_error_to_human (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct opal_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int next(struct opal_dev *dev)
{
	const struct opal_step *step;
	int state = 0, error = 0;

	do {
		step = &dev->steps[state];
		if (!step->fn)
			break;

		error = step->fn(dev, step->data);
		if (error) {
			pr_debug("Error on step function: %d with error %d: %s\n",
				 state, error,
				 opal_error_to_human(error));

			/* For each OPAL command we do a discovery0 then we
			 * start some sort of session.
			 * If we haven't passed state 1 then there was an error
			 * on discovery0 or during the attempt to start a
			 * session. Therefore we shouldn't attempt to terminate
			 * a session, as one has not yet been created.
			 */
			if (state > 1) {
				end_opal_session_error(dev);
				return error;
			}

		}
		state++;
	} while (!error);

	return error;
}