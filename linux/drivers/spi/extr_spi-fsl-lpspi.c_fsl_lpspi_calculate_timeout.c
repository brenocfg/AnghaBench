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
struct TYPE_2__ {int speed_hz; } ;
struct fsl_lpspi_data {TYPE_1__ config; } ;

/* Variables and functions */
 int MSEC_PER_SEC ; 
 int msecs_to_jiffies (int) ; 

__attribute__((used)) static int fsl_lpspi_calculate_timeout(struct fsl_lpspi_data *fsl_lpspi,
				       int size)
{
	unsigned long timeout = 0;

	/* Time with actual data transfer and CS change delay related to HW */
	timeout = (8 + 4) * size / fsl_lpspi->config.speed_hz;

	/* Add extra second for scheduler related activities */
	timeout += 1;

	/* Double calculated timeout */
	return msecs_to_jiffies(2 * timeout * MSEC_PER_SEC);
}