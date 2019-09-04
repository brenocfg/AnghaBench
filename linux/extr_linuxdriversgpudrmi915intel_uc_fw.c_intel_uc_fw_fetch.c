#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_6__ {int sw_version; } ;
struct TYPE_5__ {int sw_version; } ;
struct uc_css_header {int header_size_dw; int modulus_size_dw; int key_size_dw; int exponent_size_dw; int size_dw; TYPE_3__ huc; TYPE_2__ guc; } ;
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct intel_uc_fw {int type; int path; int header_size; int ucode_size; int rsa_size; int major_ver_found; int major_ver_wanted; int size; int /*<<< orphan*/  fetch_status; struct drm_i915_gem_object* obj; int /*<<< orphan*/  minor_ver_wanted; int /*<<< orphan*/  minor_ver_found; scalar_t__ ucode_offset; scalar_t__ rsa_offset; scalar_t__ header_offset; } ;
struct firmware {int size; scalar_t__ data; } ;
struct TYPE_4__ {struct pci_dev* pdev; } ;
struct drm_i915_private {TYPE_1__ drm; } ;
struct drm_i915_gem_object {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_NOTE (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  DRM_WARN (char*,int /*<<< orphan*/ ,...) ; 
 int ENODATA ; 
 int ENOEXEC ; 
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_FAIL ; 
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_PENDING ; 
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_SUCCESS ; 
 int /*<<< orphan*/  INTEL_UC_FIRMWARE_URL ; 
#define  INTEL_UC_FW_TYPE_GUC 129 
#define  INTEL_UC_FW_TYPE_HUC 128 
 scalar_t__ IS_ERR (struct drm_i915_gem_object*) ; 
 int /*<<< orphan*/  MISSING_CASE (int) ; 
 int PTR_ERR (struct drm_i915_gem_object*) ; 
 int UOS_RSA_SCRATCH_COUNT ; 
 struct drm_i915_gem_object* i915_gem_object_create_from_data (struct drm_i915_private*,scalar_t__,int) ; 
 int intel_uc_fw_status_repr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intel_uc_fw_type_repr (int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int,int /*<<< orphan*/ *) ; 

void intel_uc_fw_fetch(struct drm_i915_private *dev_priv,
		       struct intel_uc_fw *uc_fw)
{
	struct pci_dev *pdev = dev_priv->drm.pdev;
	struct drm_i915_gem_object *obj;
	const struct firmware *fw = NULL;
	struct uc_css_header *css;
	size_t size;
	int err;

	DRM_DEBUG_DRIVER("%s fw fetch %s\n",
			 intel_uc_fw_type_repr(uc_fw->type), uc_fw->path);

	if (!uc_fw->path)
		return;

	uc_fw->fetch_status = INTEL_UC_FIRMWARE_PENDING;
	DRM_DEBUG_DRIVER("%s fw fetch %s\n",
			 intel_uc_fw_type_repr(uc_fw->type),
			 intel_uc_fw_status_repr(uc_fw->fetch_status));

	err = request_firmware(&fw, uc_fw->path, &pdev->dev);
	if (err) {
		DRM_DEBUG_DRIVER("%s fw request_firmware err=%d\n",
				 intel_uc_fw_type_repr(uc_fw->type), err);
		goto fail;
	}

	DRM_DEBUG_DRIVER("%s fw size %zu ptr %p\n",
			 intel_uc_fw_type_repr(uc_fw->type), fw->size, fw);

	/* Check the size of the blob before examining buffer contents */
	if (fw->size < sizeof(struct uc_css_header)) {
		DRM_WARN("%s: Unexpected firmware size (%zu, min %zu)\n",
			 intel_uc_fw_type_repr(uc_fw->type),
			 fw->size, sizeof(struct uc_css_header));
		err = -ENODATA;
		goto fail;
	}

	css = (struct uc_css_header *)fw->data;

	/* Firmware bits always start from header */
	uc_fw->header_offset = 0;
	uc_fw->header_size = (css->header_size_dw - css->modulus_size_dw -
			      css->key_size_dw - css->exponent_size_dw) *
			     sizeof(u32);

	if (uc_fw->header_size != sizeof(struct uc_css_header)) {
		DRM_WARN("%s: Mismatched firmware header definition\n",
			 intel_uc_fw_type_repr(uc_fw->type));
		err = -ENOEXEC;
		goto fail;
	}

	/* then, uCode */
	uc_fw->ucode_offset = uc_fw->header_offset + uc_fw->header_size;
	uc_fw->ucode_size = (css->size_dw - css->header_size_dw) * sizeof(u32);

	/* now RSA */
	if (css->key_size_dw != UOS_RSA_SCRATCH_COUNT) {
		DRM_WARN("%s: Mismatched firmware RSA key size (%u)\n",
			 intel_uc_fw_type_repr(uc_fw->type), css->key_size_dw);
		err = -ENOEXEC;
		goto fail;
	}
	uc_fw->rsa_offset = uc_fw->ucode_offset + uc_fw->ucode_size;
	uc_fw->rsa_size = css->key_size_dw * sizeof(u32);

	/* At least, it should have header, uCode and RSA. Size of all three. */
	size = uc_fw->header_size + uc_fw->ucode_size + uc_fw->rsa_size;
	if (fw->size < size) {
		DRM_WARN("%s: Truncated firmware (%zu, expected %zu)\n",
			 intel_uc_fw_type_repr(uc_fw->type), fw->size, size);
		err = -ENOEXEC;
		goto fail;
	}

	/*
	 * The GuC firmware image has the version number embedded at a
	 * well-known offset within the firmware blob; note that major / minor
	 * version are TWO bytes each (i.e. u16), although all pointers and
	 * offsets are defined in terms of bytes (u8).
	 */
	switch (uc_fw->type) {
	case INTEL_UC_FW_TYPE_GUC:
		uc_fw->major_ver_found = css->guc.sw_version >> 16;
		uc_fw->minor_ver_found = css->guc.sw_version & 0xFFFF;
		break;

	case INTEL_UC_FW_TYPE_HUC:
		uc_fw->major_ver_found = css->huc.sw_version >> 16;
		uc_fw->minor_ver_found = css->huc.sw_version & 0xFFFF;
		break;

	default:
		MISSING_CASE(uc_fw->type);
		break;
	}

	DRM_DEBUG_DRIVER("%s fw version %u.%u (wanted %u.%u)\n",
			 intel_uc_fw_type_repr(uc_fw->type),
			 uc_fw->major_ver_found, uc_fw->minor_ver_found,
			 uc_fw->major_ver_wanted, uc_fw->minor_ver_wanted);

	if (uc_fw->major_ver_wanted == 0 && uc_fw->minor_ver_wanted == 0) {
		DRM_NOTE("%s: Skipping firmware version check\n",
			 intel_uc_fw_type_repr(uc_fw->type));
	} else if (uc_fw->major_ver_found != uc_fw->major_ver_wanted ||
		   uc_fw->minor_ver_found < uc_fw->minor_ver_wanted) {
		DRM_NOTE("%s: Wrong firmware version (%u.%u, required %u.%u)\n",
			 intel_uc_fw_type_repr(uc_fw->type),
			 uc_fw->major_ver_found, uc_fw->minor_ver_found,
			 uc_fw->major_ver_wanted, uc_fw->minor_ver_wanted);
		err = -ENOEXEC;
		goto fail;
	}

	obj = i915_gem_object_create_from_data(dev_priv, fw->data, fw->size);
	if (IS_ERR(obj)) {
		err = PTR_ERR(obj);
		DRM_DEBUG_DRIVER("%s fw object_create err=%d\n",
				 intel_uc_fw_type_repr(uc_fw->type), err);
		goto fail;
	}

	uc_fw->obj = obj;
	uc_fw->size = fw->size;
	uc_fw->fetch_status = INTEL_UC_FIRMWARE_SUCCESS;
	DRM_DEBUG_DRIVER("%s fw fetch %s\n",
			 intel_uc_fw_type_repr(uc_fw->type),
			 intel_uc_fw_status_repr(uc_fw->fetch_status));

	release_firmware(fw);
	return;

fail:
	uc_fw->fetch_status = INTEL_UC_FIRMWARE_FAIL;
	DRM_DEBUG_DRIVER("%s fw fetch %s\n",
			 intel_uc_fw_type_repr(uc_fw->type),
			 intel_uc_fw_status_repr(uc_fw->fetch_status));

	DRM_WARN("%s: Failed to fetch firmware %s (error %d)\n",
		 intel_uc_fw_type_repr(uc_fw->type), uc_fw->path, err);
	DRM_INFO("%s: Firmware can be downloaded from %s\n",
		 intel_uc_fw_type_repr(uc_fw->type), INTEL_UC_FIRMWARE_URL);

	release_firmware(fw);		/* OK even if fw is NULL */
}