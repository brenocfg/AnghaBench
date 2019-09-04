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
struct nv04_mode_state {struct nv04_crtc_reg* crtc_reg; } ;
struct nv04_crtc_reg {int /*<<< orphan*/ * Attribute; int /*<<< orphan*/ * Graphics; int /*<<< orphan*/ * Sequencer; int /*<<< orphan*/  MiscOutReg; } ;
struct drm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVSetEnablePalette (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  NVWritePRMVIO (struct drm_device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteVgaAttr (struct drm_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteVgaGr (struct drm_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteVgaSeq (struct drm_device*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_PRMVIO_MISC__WRITE ; 
 int /*<<< orphan*/  nv_lock_vga_crtc_base (struct drm_device*,int,int) ; 
 int /*<<< orphan*/  wr_cio_state (struct drm_device*,int,struct nv04_crtc_reg*,int) ; 

__attribute__((used)) static void
nv_load_state_vga(struct drm_device *dev, int head,
		  struct nv04_mode_state *state)
{
	struct nv04_crtc_reg *regp = &state->crtc_reg[head];
	int i;

	NVWritePRMVIO(dev, head, NV_PRMVIO_MISC__WRITE, regp->MiscOutReg);

	for (i = 0; i < 5; i++)
		NVWriteVgaSeq(dev, head, i, regp->Sequencer[i]);

	nv_lock_vga_crtc_base(dev, head, false);
	for (i = 0; i < 25; i++)
		wr_cio_state(dev, head, regp, i);
	nv_lock_vga_crtc_base(dev, head, true);

	for (i = 0; i < 9; i++)
		NVWriteVgaGr(dev, head, i, regp->Graphics[i]);

	NVSetEnablePalette(dev, head, true);
	for (i = 0; i < 21; i++)
		NVWriteVgaAttr(dev, head, i, regp->Attribute[i]);
	NVSetEnablePalette(dev, head, false);
}