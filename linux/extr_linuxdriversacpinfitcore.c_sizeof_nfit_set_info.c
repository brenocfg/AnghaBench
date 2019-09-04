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
struct nfit_set_info_map {int dummy; } ;
struct nfit_set_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static size_t sizeof_nfit_set_info(int num_mappings)
{
	return sizeof(struct nfit_set_info)
		+ num_mappings * sizeof(struct nfit_set_info_map);
}