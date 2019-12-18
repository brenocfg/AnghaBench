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
struct nfp_abm {int num_bands; } ;

/* Variables and functions */

__attribute__((used)) static inline bool nfp_abm_has_prio(struct nfp_abm *abm)
{
	return abm->num_bands > 1;
}