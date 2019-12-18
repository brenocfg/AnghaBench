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
struct fc_lport {int /*<<< orphan*/  e_d_tov; } ;
struct fc_frame {int dummy; } ;
struct fc_disc {scalar_t__ retry_count; scalar_t__ pending; int /*<<< orphan*/  disc_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISC_EV_FAILED ; 
 int /*<<< orphan*/  FC_DISC_DBG (struct fc_disc*,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  FC_DISC_RETRY_DELAY ; 
 scalar_t__ FC_DISC_RETRY_LIMIT ; 
 int /*<<< orphan*/  FC_EX_CLOSED ; 
 int /*<<< orphan*/  FC_EX_TIMEOUT ; 
 int /*<<< orphan*/  PTR_ERR (struct fc_frame*) ; 
 int /*<<< orphan*/  fc_disc_done (struct fc_disc*,int /*<<< orphan*/ ) ; 
 struct fc_lport* fc_disc_lport (struct fc_disc*) ; 
 unsigned long msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fc_disc_error(struct fc_disc *disc, struct fc_frame *fp)
{
	struct fc_lport *lport = fc_disc_lport(disc);
	unsigned long delay = 0;

	FC_DISC_DBG(disc, "Error %ld, retries %d/%d\n",
		    PTR_ERR(fp), disc->retry_count,
		    FC_DISC_RETRY_LIMIT);

	if (!fp || PTR_ERR(fp) == -FC_EX_TIMEOUT) {
		/*
		 * Memory allocation failure, or the exchange timed out,
		 * retry after delay.
		 */
		if (disc->retry_count < FC_DISC_RETRY_LIMIT) {
			/* go ahead and retry */
			if (!fp)
				delay = msecs_to_jiffies(FC_DISC_RETRY_DELAY);
			else {
				delay = msecs_to_jiffies(lport->e_d_tov);

				/* timeout faster first time */
				if (!disc->retry_count)
					delay /= 4;
			}
			disc->retry_count++;
			schedule_delayed_work(&disc->disc_work, delay);
		} else
			fc_disc_done(disc, DISC_EV_FAILED);
	} else if (PTR_ERR(fp) == -FC_EX_CLOSED) {
		/*
		 * if discovery fails due to lport reset, clear
		 * pending flag so that subsequent discovery can
		 * continue
		 */
		disc->pending = 0;
	}
}