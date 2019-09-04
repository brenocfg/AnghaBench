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
struct TYPE_2__ {int hmfai; } ;

/* Variables and functions */
 TYPE_1__ sclp ; 

__attribute__((used)) static inline unsigned long nonhyp_mask(int i)
{
	unsigned int nonhyp_fai = (sclp.hmfai << i * 2) >> 30;

	return 0x0000ffffffffffffUL >> (nonhyp_fai << 4);
}