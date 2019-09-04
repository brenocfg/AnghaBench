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
struct dmcu {int dummy; } ;
struct dce_dmcu {int dummy; } ;

/* Variables and functions */
 struct dce_dmcu* TO_DCE_DMCU (struct dmcu*) ; 
 int /*<<< orphan*/  kfree (struct dce_dmcu*) ; 

void dce_dmcu_destroy(struct dmcu **dmcu)
{
	struct dce_dmcu *dmcu_dce = TO_DCE_DMCU(*dmcu);

	kfree(dmcu_dce);
	*dmcu = NULL;
}