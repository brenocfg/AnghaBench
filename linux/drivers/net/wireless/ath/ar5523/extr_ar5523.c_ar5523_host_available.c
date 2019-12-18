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
struct ar5523_cmd_host_available {void* sw_ver_build; void* sw_ver_patch; void* sw_ver_minor; void* sw_ver_major; } ;
struct ar5523 {int dummy; } ;
typedef  int /*<<< orphan*/  setup ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_SW_VER_BUILD ; 
 int /*<<< orphan*/  ATH_SW_VER_MAJOR ; 
 int /*<<< orphan*/  ATH_SW_VER_MINOR ; 
 int /*<<< orphan*/  ATH_SW_VER_PATCH ; 
 int /*<<< orphan*/  WDCMSG_HOST_AVAILABLE ; 
 int ar5523_cmd_read (struct ar5523*,int /*<<< orphan*/ ,struct ar5523_cmd_host_available*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ar5523_host_available(struct ar5523 *ar)
{
	struct ar5523_cmd_host_available setup;

	/* inform target the host is available */
	setup.sw_ver_major = cpu_to_be32(ATH_SW_VER_MAJOR);
	setup.sw_ver_minor = cpu_to_be32(ATH_SW_VER_MINOR);
	setup.sw_ver_patch = cpu_to_be32(ATH_SW_VER_PATCH);
	setup.sw_ver_build = cpu_to_be32(ATH_SW_VER_BUILD);
	return ar5523_cmd_read(ar, WDCMSG_HOST_AVAILABLE,
			       &setup, sizeof(setup), NULL, 0, 0);
}