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
struct vc4_dev {int dummy; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  V3D_L2CACTL ; 
 int V3D_L2CACTL_L2CCLR ; 
 int /*<<< orphan*/  V3D_SLCACTL ; 
 int /*<<< orphan*/  V3D_SLCACTL_ICC ; 
 int /*<<< orphan*/  V3D_SLCACTL_T0CC ; 
 int /*<<< orphan*/  V3D_SLCACTL_T1CC ; 
 int /*<<< orphan*/  V3D_SLCACTL_UCC ; 
 int /*<<< orphan*/  V3D_WRITE (int /*<<< orphan*/ ,int) ; 
 int VC4_SET_FIELD (int,int /*<<< orphan*/ ) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void
vc4_flush_caches(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	/* Flush the GPU L2 caches.  These caches sit on top of system
	 * L3 (the 128kb or so shared with the CPU), and are
	 * non-allocating in the L3.
	 */
	V3D_WRITE(V3D_L2CACTL,
		  V3D_L2CACTL_L2CCLR);

	V3D_WRITE(V3D_SLCACTL,
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_T1CC) |
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_T0CC) |
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_UCC) |
		  VC4_SET_FIELD(0xf, V3D_SLCACTL_ICC));
}