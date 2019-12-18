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
typedef  int /*<<< orphan*/  u64 ;
struct intel_vgpu {int /*<<< orphan*/  scan_nonprivbb; } ;

/* Variables and functions */

__attribute__((used)) static int
vgpu_scan_nonprivbb_get(void *data, u64 *val)
{
	struct intel_vgpu *vgpu = (struct intel_vgpu *)data;
	*val = vgpu->scan_nonprivbb;
	return 0;
}