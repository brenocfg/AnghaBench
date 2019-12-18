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
struct mvebu_mpp_ctrl_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLOBAL_CONFIG_1 ; 
 int /*<<< orphan*/  GLOBAL_CONFIG_2 ; 
 unsigned int TWSI_ENABLE_OPTION1 ; 
 unsigned int TWSI_ENABLE_OPTION2 ; 
 unsigned int TWSI_ENABLE_OPTION3 ; 
 int /*<<< orphan*/  gconfmap ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int dove_twsi_ctrl_get(struct mvebu_mpp_ctrl_data *data, unsigned pid,
			      unsigned long *config)
{
	unsigned int gcfg1;
	unsigned int gcfg2;

	regmap_read(gconfmap, GLOBAL_CONFIG_1, &gcfg1);
	regmap_read(gconfmap, GLOBAL_CONFIG_2, &gcfg2);

	*config = 0;
	if (gcfg1 & TWSI_ENABLE_OPTION1)
		*config = 1;
	else if (gcfg2 & TWSI_ENABLE_OPTION2)
		*config = 2;
	else if (gcfg2 & TWSI_ENABLE_OPTION3)
		*config = 3;

	return 0;
}