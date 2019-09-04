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
struct catu_drvdata {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  CATU_STATUS ; 
 int /*<<< orphan*/  CATU_STATUS_READY ; 
 int coresight_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int catu_wait_for_ready(struct catu_drvdata *drvdata)
{
	return coresight_timeout(drvdata->base,
				 CATU_STATUS, CATU_STATUS_READY, 1);
}