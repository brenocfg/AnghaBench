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
typedef  int u32 ;
struct intel_css_header {int header_len; scalar_t__ version; } ;
struct intel_csr {scalar_t__ required_version; scalar_t__ version; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_VERSION_MAJOR (scalar_t__) ; 
 int /*<<< orphan*/  CSR_VERSION_MINOR (scalar_t__) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 parse_csr_fw_css(struct intel_csr *csr,
			    struct intel_css_header *css_header,
			    size_t rem_size)
{
	if (rem_size < sizeof(struct intel_css_header)) {
		DRM_ERROR("Truncated DMC firmware, refusing.\n");
		return 0;
	}

	if (sizeof(struct intel_css_header) !=
	    (css_header->header_len * 4)) {
		DRM_ERROR("DMC firmware has wrong CSS header length "
			  "(%u bytes)\n",
			  (css_header->header_len * 4));
		return 0;
	}

	if (csr->required_version &&
	    css_header->version != csr->required_version) {
		DRM_INFO("Refusing to load DMC firmware v%u.%u,"
			 " please use v%u.%u\n",
			 CSR_VERSION_MAJOR(css_header->version),
			 CSR_VERSION_MINOR(css_header->version),
			 CSR_VERSION_MAJOR(csr->required_version),
			 CSR_VERSION_MINOR(csr->required_version));
		return 0;
	}

	csr->version = css_header->version;

	return sizeof(struct intel_css_header);
}