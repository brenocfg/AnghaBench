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
struct radeon_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  R600_CTXCGTT3DRPHC_DFLT ; 
 int /*<<< orphan*/  R600_CTXCGTT3DRSDC_DFLT ; 
 int /*<<< orphan*/  R600_VDDC3DOORPHC_DFLT ; 
 int /*<<< orphan*/  R600_VDDC3DOORSDC_DFLT ; 
 int /*<<< orphan*/  R600_VDDC3DOORSU_DFLT ; 
 int /*<<< orphan*/  r600_set_ctxcgtt3d_rphc (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_set_ctxcgtt3d_rsdc (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_set_vddc3d_oorphc (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_set_vddc3d_oorsdc (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r600_set_vddc3d_oorsu (struct radeon_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rv6xx_program_vddc3d_parameters(struct radeon_device *rdev)
{
	r600_set_vddc3d_oorsu(rdev, R600_VDDC3DOORSU_DFLT);
	r600_set_vddc3d_oorphc(rdev, R600_VDDC3DOORPHC_DFLT);
	r600_set_vddc3d_oorsdc(rdev, R600_VDDC3DOORSDC_DFLT);
	r600_set_ctxcgtt3d_rphc(rdev, R600_CTXCGTT3DRPHC_DFLT);
	r600_set_ctxcgtt3d_rsdc(rdev, R600_CTXCGTT3DRSDC_DFLT);
}