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
struct mga_device {int dummy; } ;
struct drm_crtc {TYPE_1__* dev; } ;
struct TYPE_2__ {struct mga_device* dev_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_DATA ; 
 int /*<<< orphan*/  DAC_INDEX ; 
 int MGA1064_GEN_IO_DATA ; 
 int MGA1064_REMHEADCTL2 ; 
 int MGA1064_SPAREREG ; 
 int /*<<< orphan*/  MGAREG_CRTCEXT_DATA ; 
 int /*<<< orphan*/  MGAREG_CRTCEXT_INDEX ; 
 int RREG8 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WREG8 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WREG_DAC (int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void mga_g200wb_commit(struct drm_crtc *crtc)
{
	u8 tmp;
	struct mga_device *mdev = crtc->dev->dev_private;

	/* 1- The first step is to ensure that the vrsten and hrsten are set */
	WREG8(MGAREG_CRTCEXT_INDEX, 1);
	tmp = RREG8(MGAREG_CRTCEXT_DATA);
	WREG8(MGAREG_CRTCEXT_DATA, tmp | 0x88);

	/* 2- second step is to assert the rstlvl2 */
	WREG8(DAC_INDEX, MGA1064_REMHEADCTL2);
	tmp = RREG8(DAC_DATA);
	tmp |= 0x8;
	WREG8(DAC_DATA, tmp);

	/* wait 10 us */
	udelay(10);

	/* 3- deassert rstlvl2 */
	tmp &= ~0x08;
	WREG8(DAC_INDEX, MGA1064_REMHEADCTL2);
	WREG8(DAC_DATA, tmp);

	/* 4- remove mask of scan request */
	WREG8(DAC_INDEX, MGA1064_SPAREREG);
	tmp = RREG8(DAC_DATA);
	tmp &= ~0x80;
	WREG8(DAC_DATA, tmp);

	/* 5- put back a 0 on the misc<0> line */
	WREG8(DAC_INDEX, MGA1064_GEN_IO_DATA);
	tmp = RREG8(DAC_DATA);
	tmp &= ~0x10;
	WREG_DAC(MGA1064_GEN_IO_DATA, tmp);
}