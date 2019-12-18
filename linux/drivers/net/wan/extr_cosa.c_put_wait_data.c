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
struct cosa_data {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int SR_TX_RDY ; 
 int cosa_getstatus (struct cosa_data*) ; 
 int /*<<< orphan*/  cosa_putdata8 (struct cosa_data*,int) ; 
 int /*<<< orphan*/  pr_info (char*,int,...) ; 
 int /*<<< orphan*/  schedule_timeout_interruptible (int) ; 

__attribute__((used)) static int put_wait_data(struct cosa_data *cosa, int data)
{
	int retries = 1000;
	while (--retries) {
		/* read data and return them */
		if (cosa_getstatus(cosa) & SR_TX_RDY) {
			cosa_putdata8(cosa, data);
#if 0
			pr_info("Putdata: %d retries\n", 999-retries);
#endif
			return 0;
		}
#if 0
		/* sleep if not ready to read */
		schedule_timeout_interruptible(1);
#endif
	}
	pr_info("cosa%d: timeout in put_wait_data (status 0x%x)\n",
		cosa->num, cosa_getstatus(cosa));
	return -1;
}