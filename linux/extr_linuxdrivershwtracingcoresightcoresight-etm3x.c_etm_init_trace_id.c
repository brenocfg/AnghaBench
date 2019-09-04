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
struct etm_drvdata {int /*<<< orphan*/  cpu; int /*<<< orphan*/  traceid; } ;

/* Variables and functions */
 int /*<<< orphan*/  coresight_get_trace_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void etm_init_trace_id(struct etm_drvdata *drvdata)
{
	drvdata->traceid = coresight_get_trace_id(drvdata->cpu);
}