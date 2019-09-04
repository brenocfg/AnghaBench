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
typedef  scalar_t__ uint32_t ;
struct stepping_info {char stepping; char substepping; } ;
struct intel_package_header {int header_len; scalar_t__ num_entries; TYPE_1__* fw_info; } ;
struct intel_dmc_header {int header_len; scalar_t__ mmio_count; int fw_size; int /*<<< orphan*/ * mmiodata; int /*<<< orphan*/ * mmioaddr; } ;
struct intel_css_header {int header_len; scalar_t__ version; } ;
struct intel_csr {scalar_t__ version; scalar_t__ fw_path; scalar_t__ mmio_count; int dmc_fw_size; int /*<<< orphan*/ * mmiodata; int /*<<< orphan*/ * mmioaddr; } ;
struct firmware {int /*<<< orphan*/ * data; } ;
struct drm_i915_private {struct intel_csr csr; } ;
struct TYPE_4__ {scalar_t__ dmc_firmware_path; } ;
struct TYPE_3__ {char substepping; char stepping; scalar_t__ offset; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ BXT_CSR_VERSION_REQUIRED ; 
 scalar_t__ CNL_CSR_VERSION_REQUIRED ; 
 scalar_t__ CSR_DEFAULT_FW_OFFSET ; 
 scalar_t__ CSR_MAX_FW_SIZE ; 
 int /*<<< orphan*/  CSR_MMIO_END_RANGE ; 
 int /*<<< orphan*/  CSR_MMIO_START_RANGE ; 
 int /*<<< orphan*/  CSR_VERSION_MAJOR (scalar_t__) ; 
 int /*<<< orphan*/  CSR_VERSION_MINOR (scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ GLK_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/  INTEL_REVID (struct drm_i915_private*) ; 
 scalar_t__ IS_BROXTON (struct drm_i915_private*) ; 
 scalar_t__ IS_CANNONLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_COFFEELAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_GEMINILAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_KABYLAKE (struct drm_i915_private*) ; 
 scalar_t__ IS_SKYLAKE (struct drm_i915_private*) ; 
 scalar_t__ KBL_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/  MISSING_CASE (int /*<<< orphan*/ ) ; 
 scalar_t__ SKL_CSR_VERSION_REQUIRED ; 
 int /*<<< orphan*/  _MMIO (int /*<<< orphan*/ ) ; 
 TYPE_2__ i915_modparams ; 
 struct stepping_info* intel_get_stepping_info (struct drm_i915_private*) ; 
 scalar_t__* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__* memcpy (scalar_t__*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static uint32_t *parse_csr_fw(struct drm_i915_private *dev_priv,
			      const struct firmware *fw)
{
	struct intel_css_header *css_header;
	struct intel_package_header *package_header;
	struct intel_dmc_header *dmc_header;
	struct intel_csr *csr = &dev_priv->csr;
	const struct stepping_info *si = intel_get_stepping_info(dev_priv);
	uint32_t dmc_offset = CSR_DEFAULT_FW_OFFSET, readcount = 0, nbytes;
	uint32_t i;
	uint32_t *dmc_payload;
	uint32_t required_version;

	if (!fw)
		return NULL;

	/* Extract CSS Header information*/
	css_header = (struct intel_css_header *)fw->data;
	if (sizeof(struct intel_css_header) !=
	    (css_header->header_len * 4)) {
		DRM_ERROR("DMC firmware has wrong CSS header length "
			  "(%u bytes)\n",
			  (css_header->header_len * 4));
		return NULL;
	}

	csr->version = css_header->version;

	if (csr->fw_path == i915_modparams.dmc_firmware_path) {
		/* Bypass version check for firmware override. */
		required_version = csr->version;
	} else if (IS_CANNONLAKE(dev_priv)) {
		required_version = CNL_CSR_VERSION_REQUIRED;
	} else if (IS_GEMINILAKE(dev_priv)) {
		required_version = GLK_CSR_VERSION_REQUIRED;
	} else if (IS_KABYLAKE(dev_priv) || IS_COFFEELAKE(dev_priv)) {
		required_version = KBL_CSR_VERSION_REQUIRED;
	} else if (IS_SKYLAKE(dev_priv)) {
		required_version = SKL_CSR_VERSION_REQUIRED;
	} else if (IS_BROXTON(dev_priv)) {
		required_version = BXT_CSR_VERSION_REQUIRED;
	} else {
		MISSING_CASE(INTEL_REVID(dev_priv));
		required_version = 0;
	}

	if (csr->version != required_version) {
		DRM_INFO("Refusing to load DMC firmware v%u.%u,"
			 " please use v%u.%u\n",
			 CSR_VERSION_MAJOR(csr->version),
			 CSR_VERSION_MINOR(csr->version),
			 CSR_VERSION_MAJOR(required_version),
			 CSR_VERSION_MINOR(required_version));
		return NULL;
	}

	readcount += sizeof(struct intel_css_header);

	/* Extract Package Header information*/
	package_header = (struct intel_package_header *)
		&fw->data[readcount];
	if (sizeof(struct intel_package_header) !=
	    (package_header->header_len * 4)) {
		DRM_ERROR("DMC firmware has wrong package header length "
			  "(%u bytes)\n",
			  (package_header->header_len * 4));
		return NULL;
	}
	readcount += sizeof(struct intel_package_header);

	/* Search for dmc_offset to find firware binary. */
	for (i = 0; i < package_header->num_entries; i++) {
		if (package_header->fw_info[i].substepping == '*' &&
		    si->stepping == package_header->fw_info[i].stepping) {
			dmc_offset = package_header->fw_info[i].offset;
			break;
		} else if (si->stepping == package_header->fw_info[i].stepping &&
			   si->substepping == package_header->fw_info[i].substepping) {
			dmc_offset = package_header->fw_info[i].offset;
			break;
		} else if (package_header->fw_info[i].stepping == '*' &&
			   package_header->fw_info[i].substepping == '*')
			dmc_offset = package_header->fw_info[i].offset;
	}
	if (dmc_offset == CSR_DEFAULT_FW_OFFSET) {
		DRM_ERROR("DMC firmware not supported for %c stepping\n",
			  si->stepping);
		return NULL;
	}
	readcount += dmc_offset;

	/* Extract dmc_header information. */
	dmc_header = (struct intel_dmc_header *)&fw->data[readcount];
	if (sizeof(struct intel_dmc_header) != (dmc_header->header_len)) {
		DRM_ERROR("DMC firmware has wrong dmc header length "
			  "(%u bytes)\n",
			  (dmc_header->header_len));
		return NULL;
	}
	readcount += sizeof(struct intel_dmc_header);

	/* Cache the dmc header info. */
	if (dmc_header->mmio_count > ARRAY_SIZE(csr->mmioaddr)) {
		DRM_ERROR("DMC firmware has wrong mmio count %u\n",
			  dmc_header->mmio_count);
		return NULL;
	}
	csr->mmio_count = dmc_header->mmio_count;
	for (i = 0; i < dmc_header->mmio_count; i++) {
		if (dmc_header->mmioaddr[i] < CSR_MMIO_START_RANGE ||
		    dmc_header->mmioaddr[i] > CSR_MMIO_END_RANGE) {
			DRM_ERROR("DMC firmware has wrong mmio address 0x%x\n",
				  dmc_header->mmioaddr[i]);
			return NULL;
		}
		csr->mmioaddr[i] = _MMIO(dmc_header->mmioaddr[i]);
		csr->mmiodata[i] = dmc_header->mmiodata[i];
	}

	/* fw_size is in dwords, so multiplied by 4 to convert into bytes. */
	nbytes = dmc_header->fw_size * 4;
	if (nbytes > CSR_MAX_FW_SIZE) {
		DRM_ERROR("DMC firmware too big (%u bytes)\n", nbytes);
		return NULL;
	}
	csr->dmc_fw_size = dmc_header->fw_size;

	dmc_payload = kmalloc(nbytes, GFP_KERNEL);
	if (!dmc_payload) {
		DRM_ERROR("Memory allocation failed for dmc payload\n");
		return NULL;
	}

	return memcpy(dmc_payload, &fw->data[readcount], nbytes);
}