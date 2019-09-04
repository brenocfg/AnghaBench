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
 int /*<<< orphan*/  CCDC_SYN_MODE ; 
 int regr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ccdc_getfid(void)
{
	return (regr(CCDC_SYN_MODE) >> 15) & 1;
}