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
struct nfp_insn_meta {scalar_t__ subprog_idx; } ;

/* Variables and functions */

__attribute__((used)) static bool nfp_is_main_function(struct nfp_insn_meta *meta)
{
	return meta->subprog_idx == 0;
}