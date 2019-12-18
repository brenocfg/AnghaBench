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
struct replicator_drvdata {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  dynamic_replicator_reset (struct replicator_drvdata*) ; 

__attribute__((used)) static inline void replicator_reset(struct replicator_drvdata *drvdata)
{
	if (drvdata->base)
		dynamic_replicator_reset(drvdata);
}