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
struct cosa_data {int dummy; } ;

/* Variables and functions */
 int SR_RX_RDY ; 
 short cosa_getdata8 (struct cosa_data*) ; 
 int cosa_getstatus (struct cosa_data*) ; 
 int /*<<< orphan*/  pr_info (char*,int) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 

__attribute__((used)) static int get_wait_data(struct cosa_data *cosa)
{
	int retries = 1000;

	while (--retries) {
		/* read data and return them */
		if (cosa_getstatus(cosa) & SR_RX_RDY) {
			short r;
			r = cosa_getdata8(cosa);
#if 0
			pr_info("get_wait_data returning after %d retries\n",
				999-retries);
#endif
			return r;
		}
		/* sleep if not ready to read */
		schedule_timeout_interruptible(1);
	}
	pr_info("timeout in get_wait_data (status 0x%x)\n",
		cosa_getstatus(cosa));
	return -1;
}