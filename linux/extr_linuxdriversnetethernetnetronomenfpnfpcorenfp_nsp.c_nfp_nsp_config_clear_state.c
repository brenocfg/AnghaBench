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
struct nfp_nsp {scalar_t__ idx; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */

void nfp_nsp_config_clear_state(struct nfp_nsp *state)
{
	state->entries = NULL;
	state->idx = 0;
}