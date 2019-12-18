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
struct ap_matrix {int apm_max; int aqm_max; int adm_max; } ;
struct ap_config_info {int Na; int Nd; scalar_t__ apxa; } ;

/* Variables and functions */

__attribute__((used)) static void vfio_ap_matrix_init(struct ap_config_info *info,
				struct ap_matrix *matrix)
{
	matrix->apm_max = info->apxa ? info->Na : 63;
	matrix->aqm_max = info->apxa ? info->Nd : 15;
	matrix->adm_max = info->apxa ? info->Nd : 15;
}