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
typedef  unsigned long u16 ;
struct edc {unsigned long timestart; int errorcount; } ;

/* Variables and functions */
 unsigned long jiffies ; 

__attribute__((used)) static inline int edc_inc(struct edc *err_hist, u16 max_err, u16 timeframe)
{
	unsigned long now;

	now = jiffies;
	if (now - err_hist->timestart > timeframe) {
		err_hist->errorcount = 1;
		err_hist->timestart = now;
	} else if (++err_hist->errorcount > max_err) {
			err_hist->errorcount = 0;
			err_hist->timestart = now;
			return 1;
	}
	return 0;
}