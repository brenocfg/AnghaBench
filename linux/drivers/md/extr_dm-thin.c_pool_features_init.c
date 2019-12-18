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
struct pool_features {int zero_new_blocks; int discard_enabled; int discard_passdown; int error_if_no_space; int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_WRITE ; 

__attribute__((used)) static void pool_features_init(struct pool_features *pf)
{
	pf->mode = PM_WRITE;
	pf->zero_new_blocks = true;
	pf->discard_enabled = true;
	pf->discard_passdown = true;
	pf->error_if_no_space = false;
}