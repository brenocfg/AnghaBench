#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct nvif_object {int dummy; } ;
struct TYPE_3__ {struct nvif_object object; } ;
struct TYPE_4__ {TYPE_1__ device; } ;
struct nouveau_drm {TYPE_2__ client; } ;
struct drm_encoder {struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct drm_connector {int dummy; } ;
typedef  enum drm_connector_status { ____Placeholder_drm_connector_status } drm_connector_status ;

/* Variables and functions */
 int MASK (int /*<<< orphan*/ ) ; 
 int MAX_SAMPLE_PAIRS ; 
 int NVReadRAMDAC (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NVReadVgaCrtc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NVReadVgaSeq (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVSetOwner (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVWriteRAMDAC (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NVWriteVgaCrtc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NVWriteVgaSeq (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NV_CIO_CRE_PIXEL_FORMAT ; 
 int /*<<< orphan*/  NV_CIO_CRE_PIXEL_INDEX ; 
 int /*<<< orphan*/  NV_CIO_CRE_RPC1_INDEX ; 
 int /*<<< orphan*/  NV_CIO_CR_MODE_INDEX ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  NV_PRAMDAC_GENERAL_CONTROL ; 
 int NV_PRAMDAC_GENERAL_CONTROL_BPC_8BITS ; 
 int NV_PRAMDAC_GENERAL_CONTROL_PIXMIX_ON ; 
 int NV_PRAMDAC_GENERAL_CONTROL_TERMINATION_75OHM ; 
 int /*<<< orphan*/  NV_PRAMDAC_TEST_CONTROL ; 
 int NV_PRAMDAC_TEST_CONTROL_PWRDWN_DAC_OFF ; 
 int /*<<< orphan*/  NV_PRMDIO_PALETTE_DATA ; 
 int /*<<< orphan*/  NV_PRMDIO_PIXEL_MASK ; 
 int /*<<< orphan*/  NV_PRMDIO_READ_MODE_ADDRESS ; 
 int /*<<< orphan*/  NV_PRMDIO_WRITE_MODE_ADDRESS ; 
 int /*<<< orphan*/  NV_VIO_SR_CLOCK_INDEX ; 
 int connector_status_connected ; 
 int connector_status_disconnected ; 
 int /*<<< orphan*/  msleep (int) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 scalar_t__ nv_two_heads (struct drm_device*) ; 
 int nvif_rd08 (struct nvif_object*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvif_wr08 (struct nvif_object*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sample_load_twice (struct drm_device*,int*) ; 

__attribute__((used)) static enum drm_connector_status nv04_dac_detect(struct drm_encoder *encoder,
						 struct drm_connector *connector)
{
	struct drm_device *dev = encoder->dev;
	struct nvif_object *device = &nouveau_drm(dev)->client.device.object;
	struct nouveau_drm *drm = nouveau_drm(dev);
	uint8_t saved_seq1, saved_pi, saved_rpc1, saved_cr_mode;
	uint8_t saved_palette0[3], saved_palette_mask;
	uint32_t saved_rtest_ctrl, saved_rgen_ctrl;
	int i;
	uint8_t blue;
	bool sense = true;

	/*
	 * for this detection to work, there needs to be a mode set up on the
	 * CRTC.  this is presumed to be the case
	 */

	if (nv_two_heads(dev))
		/* only implemented for head A for now */
		NVSetOwner(dev, 0);

	saved_cr_mode = NVReadVgaCrtc(dev, 0, NV_CIO_CR_MODE_INDEX);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CR_MODE_INDEX, saved_cr_mode | 0x80);

	saved_seq1 = NVReadVgaSeq(dev, 0, NV_VIO_SR_CLOCK_INDEX);
	NVWriteVgaSeq(dev, 0, NV_VIO_SR_CLOCK_INDEX, saved_seq1 & ~0x20);

	saved_rtest_ctrl = NVReadRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL,
		      saved_rtest_ctrl & ~NV_PRAMDAC_TEST_CONTROL_PWRDWN_DAC_OFF);

	msleep(10);

	saved_pi = NVReadVgaCrtc(dev, 0, NV_CIO_CRE_PIXEL_INDEX);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_PIXEL_INDEX,
		       saved_pi & ~(0x80 | MASK(NV_CIO_CRE_PIXEL_FORMAT)));
	saved_rpc1 = NVReadVgaCrtc(dev, 0, NV_CIO_CRE_RPC1_INDEX);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_RPC1_INDEX, saved_rpc1 & ~0xc0);

	nvif_wr08(device, NV_PRMDIO_READ_MODE_ADDRESS, 0x0);
	for (i = 0; i < 3; i++)
		saved_palette0[i] = nvif_rd08(device, NV_PRMDIO_PALETTE_DATA);
	saved_palette_mask = nvif_rd08(device, NV_PRMDIO_PIXEL_MASK);
	nvif_wr08(device, NV_PRMDIO_PIXEL_MASK, 0);

	saved_rgen_ctrl = NVReadRAMDAC(dev, 0, NV_PRAMDAC_GENERAL_CONTROL);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_GENERAL_CONTROL,
		      (saved_rgen_ctrl & ~(NV_PRAMDAC_GENERAL_CONTROL_BPC_8BITS |
					   NV_PRAMDAC_GENERAL_CONTROL_TERMINATION_75OHM)) |
		      NV_PRAMDAC_GENERAL_CONTROL_PIXMIX_ON);

	blue = 8;	/* start of test range */

	do {
		bool sense_pair[2];

		nvif_wr08(device, NV_PRMDIO_WRITE_MODE_ADDRESS, 0);
		nvif_wr08(device, NV_PRMDIO_PALETTE_DATA, 0);
		nvif_wr08(device, NV_PRMDIO_PALETTE_DATA, 0);
		/* testing blue won't find monochrome monitors.  I don't care */
		nvif_wr08(device, NV_PRMDIO_PALETTE_DATA, blue);

		i = 0;
		/* take sample pairs until both samples in the pair agree */
		do {
			if (sample_load_twice(dev, sense_pair))
				goto out;
		} while ((sense_pair[0] != sense_pair[1]) &&
							++i < MAX_SAMPLE_PAIRS);

		if (i == MAX_SAMPLE_PAIRS)
			/* too much oscillation defaults to LO */
			sense = false;
		else
			sense = sense_pair[0];

	/*
	 * if sense goes LO before blue ramps to 0x18, monitor is not connected.
	 * ergo, if blue gets to 0x18, monitor must be connected
	 */
	} while (++blue < 0x18 && sense);

out:
	nvif_wr08(device, NV_PRMDIO_PIXEL_MASK, saved_palette_mask);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_GENERAL_CONTROL, saved_rgen_ctrl);
	nvif_wr08(device, NV_PRMDIO_WRITE_MODE_ADDRESS, 0);
	for (i = 0; i < 3; i++)
		nvif_wr08(device, NV_PRMDIO_PALETTE_DATA, saved_palette0[i]);
	NVWriteRAMDAC(dev, 0, NV_PRAMDAC_TEST_CONTROL, saved_rtest_ctrl);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_PIXEL_INDEX, saved_pi);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CRE_RPC1_INDEX, saved_rpc1);
	NVWriteVgaSeq(dev, 0, NV_VIO_SR_CLOCK_INDEX, saved_seq1);
	NVWriteVgaCrtc(dev, 0, NV_CIO_CR_MODE_INDEX, saved_cr_mode);

	if (blue == 0x18) {
		NV_DEBUG(drm, "Load detected on head A\n");
		return connector_status_connected;
	}

	return connector_status_disconnected;
}