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
typedef  scalar_t__ u32 ;
struct sdma_engine {TYPE_1__* drvdata; } ;
struct TYPE_2__ {scalar_t__ chnenbl0; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 chnenbl_ofs(struct sdma_engine *sdma, unsigned int event)
{
	u32 chnenbl0 = sdma->drvdata->chnenbl0;
	return chnenbl0 + event * 4;
}