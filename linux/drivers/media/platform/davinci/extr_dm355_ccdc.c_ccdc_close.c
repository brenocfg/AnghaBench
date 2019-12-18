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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPSS_CCDC_CLOCK ; 
 int /*<<< orphan*/  vpss_enable_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccdc_close(struct device *device)
{
	/* disable clock */
	vpss_enable_clock(VPSS_CCDC_CLOCK, 0);
	/* do nothing for now */
	return 0;
}