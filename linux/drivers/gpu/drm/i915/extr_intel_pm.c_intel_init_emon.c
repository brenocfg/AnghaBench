#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_2__ {int corr; } ;
struct drm_i915_private {TYPE_1__ ips; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSIEW0 ; 
 int /*<<< orphan*/  CSIEW1 ; 
 int /*<<< orphan*/  CSIEW2 ; 
 int /*<<< orphan*/  DEW (int) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned long) ; 
 int /*<<< orphan*/  ECR ; 
 int /*<<< orphan*/  EG0 ; 
 int /*<<< orphan*/  EG1 ; 
 int /*<<< orphan*/  EG2 ; 
 int /*<<< orphan*/  EG3 ; 
 int /*<<< orphan*/  EG4 ; 
 int /*<<< orphan*/  EG5 ; 
 int /*<<< orphan*/  EG6 ; 
 int /*<<< orphan*/  EG7 ; 
 int I915_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I915_WRITE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LCFUSE02 ; 
 int LCFUSE_HIV_MASK ; 
 int /*<<< orphan*/  OGW0 ; 
 int /*<<< orphan*/  OGW1 ; 
 int /*<<< orphan*/  PEW (int) ; 
 int /*<<< orphan*/  POSTING_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PXVFREQ (int) ; 
 int PXVFREQ_PX_MASK ; 
 int PXVFREQ_PX_SHIFT ; 
 int /*<<< orphan*/  PXW (int) ; 
 int /*<<< orphan*/  PXWL (int) ; 
 int /*<<< orphan*/  SDEW ; 
 unsigned long intel_pxfreq (int) ; 

__attribute__((used)) static void intel_init_emon(struct drm_i915_private *dev_priv)
{
	u32 lcfuse;
	u8 pxw[16];
	int i;

	/* Disable to program */
	I915_WRITE(ECR, 0);
	POSTING_READ(ECR);

	/* Program energy weights for various events */
	I915_WRITE(SDEW, 0x15040d00);
	I915_WRITE(CSIEW0, 0x007f0000);
	I915_WRITE(CSIEW1, 0x1e220004);
	I915_WRITE(CSIEW2, 0x04000004);

	for (i = 0; i < 5; i++)
		I915_WRITE(PEW(i), 0);
	for (i = 0; i < 3; i++)
		I915_WRITE(DEW(i), 0);

	/* Program P-state weights to account for frequency power adjustment */
	for (i = 0; i < 16; i++) {
		u32 pxvidfreq = I915_READ(PXVFREQ(i));
		unsigned long freq = intel_pxfreq(pxvidfreq);
		unsigned long vid = (pxvidfreq & PXVFREQ_PX_MASK) >>
			PXVFREQ_PX_SHIFT;
		unsigned long val;

		val = vid * vid;
		val *= (freq / 1000);
		val *= 255;
		val /= (127*127*900);
		if (val > 0xff)
			DRM_ERROR("bad pxval: %ld\n", val);
		pxw[i] = val;
	}
	/* Render standby states get 0 weight */
	pxw[14] = 0;
	pxw[15] = 0;

	for (i = 0; i < 4; i++) {
		u32 val = (pxw[i*4] << 24) | (pxw[(i*4)+1] << 16) |
			(pxw[(i*4)+2] << 8) | (pxw[(i*4)+3]);
		I915_WRITE(PXW(i), val);
	}

	/* Adjust magic regs to magic values (more experimental results) */
	I915_WRITE(OGW0, 0);
	I915_WRITE(OGW1, 0);
	I915_WRITE(EG0, 0x00007f00);
	I915_WRITE(EG1, 0x0000000e);
	I915_WRITE(EG2, 0x000e0000);
	I915_WRITE(EG3, 0x68000300);
	I915_WRITE(EG4, 0x42000000);
	I915_WRITE(EG5, 0x00140031);
	I915_WRITE(EG6, 0);
	I915_WRITE(EG7, 0);

	for (i = 0; i < 8; i++)
		I915_WRITE(PXWL(i), 0);

	/* Enable PMON + select events */
	I915_WRITE(ECR, 0x80000019);

	lcfuse = I915_READ(LCFUSE02);

	dev_priv->ips.corr = (lcfuse & LCFUSE_HIV_MASK);
}