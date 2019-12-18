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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct smiapp_sensor {TYPE_1__ pll; } ;

/* Variables and functions */
 int /*<<< orphan*/  SMIAPP_PLL_FLAG_OP_PIX_CLOCK_PER_LANE ; 

__attribute__((used)) static int jt8ev1_init(struct smiapp_sensor *sensor)
{
	sensor->pll.flags |= SMIAPP_PLL_FLAG_OP_PIX_CLOCK_PER_LANE;

	return 0;
}