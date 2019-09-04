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
 int /*<<< orphan*/  IMCR_L1DCFG ; 
 int /*<<< orphan*/  IMCR_L1PCFG ; 
 unsigned int imcr_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imcr_set (int /*<<< orphan*/ ,int) ; 

void L1_cache_on(void)
{
	unsigned int dummy;

	imcr_set(IMCR_L1PCFG, 7);
	dummy = imcr_get(IMCR_L1PCFG);

	imcr_set(IMCR_L1DCFG, 7);
	dummy = imcr_get(IMCR_L1DCFG);
}