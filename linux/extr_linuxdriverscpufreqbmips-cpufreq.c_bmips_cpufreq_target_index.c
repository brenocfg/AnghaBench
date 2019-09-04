#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct cpufreq_policy {TYPE_1__* freq_table; } ;
struct TYPE_4__ {int bmips_type; } ;
struct TYPE_3__ {unsigned int driver_data; } ;

/* Variables and functions */
#define  BMIPS5000 129 
#define  BMIPS5200 128 
 unsigned int BMIPS5_CLK_DIV_MASK ; 
 int BMIPS5_CLK_DIV_SET_SHIFT ; 
 unsigned int BMIPS5_CLK_DIV_SHIFT ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  change_c0_brcm_mode (unsigned int,int) ; 
 TYPE_2__* priv ; 

__attribute__((used)) static int bmips_cpufreq_target_index(struct cpufreq_policy *policy,
				      unsigned int index)
{
	unsigned int div = policy->freq_table[index].driver_data;

	switch (priv->bmips_type) {
	case BMIPS5200:
	case BMIPS5000:
		change_c0_brcm_mode(BMIPS5_CLK_DIV_MASK << BMIPS5_CLK_DIV_SHIFT,
				    (1 << BMIPS5_CLK_DIV_SET_SHIFT) |
				    (div << BMIPS5_CLK_DIV_SHIFT));
		break;
	default:
		return -ENOTSUPP;
	}

	return 0;
}