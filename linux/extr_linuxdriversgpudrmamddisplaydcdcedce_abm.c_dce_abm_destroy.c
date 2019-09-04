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
struct dce_abm {int dummy; } ;
struct abm {int dummy; } ;

/* Variables and functions */
 struct dce_abm* TO_DCE_ABM (struct abm*) ; 
 int /*<<< orphan*/  kfree (struct dce_abm*) ; 

void dce_abm_destroy(struct abm **abm)
{
	struct dce_abm *abm_dce = TO_DCE_ABM(*abm);

	kfree(abm_dce);
	*abm = NULL;
}