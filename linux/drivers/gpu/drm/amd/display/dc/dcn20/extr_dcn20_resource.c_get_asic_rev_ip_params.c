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
typedef  int /*<<< orphan*/  uint32_t ;
struct _vcs_dpi_ip_params_st {int dummy; } ;

/* Variables and functions */
 struct _vcs_dpi_ip_params_st dcn2_0_ip ; 

__attribute__((used)) static struct _vcs_dpi_ip_params_st *get_asic_rev_ip_params(
	uint32_t hw_internal_rev)
{
	/* NV12 and NV10 */
	return &dcn2_0_ip;
}