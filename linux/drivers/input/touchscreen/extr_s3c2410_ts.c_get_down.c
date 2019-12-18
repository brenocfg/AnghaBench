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

/* Variables and functions */
 unsigned long S3C2410_ADCDAT0_UPDOWN ; 

__attribute__((used)) static inline bool get_down(unsigned long data0, unsigned long data1)
{
	/* returns true if both data values show stylus down */
	return (!(data0 & S3C2410_ADCDAT0_UPDOWN) &&
		!(data1 & S3C2410_ADCDAT0_UPDOWN));
}