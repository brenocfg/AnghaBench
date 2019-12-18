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
struct sr_tmon {int /*<<< orphan*/  tmon_id; struct sr_thermal* priv; } ;
struct sr_thermal {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ SR_TMON_TEMP_BASE (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 

__attribute__((used)) static int sr_get_temp(void *data, int *temp)
{
	struct sr_tmon *tmon = data;
	struct sr_thermal *sr_thermal = tmon->priv;

	*temp = readl(sr_thermal->regs + SR_TMON_TEMP_BASE(tmon->tmon_id));

	return 0;
}