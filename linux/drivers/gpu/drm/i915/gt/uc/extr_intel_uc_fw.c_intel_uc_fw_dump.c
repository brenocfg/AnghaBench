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
struct intel_uc_fw {int /*<<< orphan*/  rsa_size; int /*<<< orphan*/  ucode_size; int /*<<< orphan*/  minor_ver_found; int /*<<< orphan*/  major_ver_found; int /*<<< orphan*/  minor_ver_wanted; int /*<<< orphan*/  major_ver_wanted; int /*<<< orphan*/  status; int /*<<< orphan*/  path; int /*<<< orphan*/  type; } ;
struct drm_printer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  intel_uc_fw_status_repr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_fw_type_repr (int /*<<< orphan*/ ) ; 

void intel_uc_fw_dump(const struct intel_uc_fw *uc_fw, struct drm_printer *p)
{
	drm_printf(p, "%s firmware: %s\n",
		   intel_uc_fw_type_repr(uc_fw->type), uc_fw->path);
	drm_printf(p, "\tstatus: %s\n",
		   intel_uc_fw_status_repr(uc_fw->status));
	drm_printf(p, "\tversion: wanted %u.%u, found %u.%u\n",
		   uc_fw->major_ver_wanted, uc_fw->minor_ver_wanted,
		   uc_fw->major_ver_found, uc_fw->minor_ver_found);
	drm_printf(p, "\tuCode: %u bytes\n", uc_fw->ucode_size);
	drm_printf(p, "\tRSA: %u bytes\n", uc_fw->rsa_size);
}