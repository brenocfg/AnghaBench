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
struct nfp_nffw_info {int /*<<< orphan*/  res; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfp_nffw_info*) ; 
 int /*<<< orphan*/  nfp_resource_release (int /*<<< orphan*/ ) ; 

void nfp_nffw_info_close(struct nfp_nffw_info *state)
{
	nfp_resource_release(state->res);
	kfree(state);
}