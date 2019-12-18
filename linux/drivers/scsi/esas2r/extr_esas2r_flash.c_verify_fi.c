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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  scalar_t__ u16 ;
struct esas2r_flash_img {int length; scalar_t__ adap_typ; scalar_t__ num_comps; scalar_t__ checksum; void* status; struct esas2r_component_header* cmp_hdr; } ;
struct esas2r_flash_context {int fi_hdr_len; struct esas2r_flash_img* fi; } ;
struct esas2r_component_header {scalar_t__ img_type; int length; void* status; int /*<<< orphan*/  image_offset; } ;
struct esas2r_adapter {int dummy; } ;

/* Variables and functions */
#define  CH_IT_BIOS 133 
#define  CH_IT_CFG 132 
#define  CH_IT_EFI 131 
#define  CH_IT_FW 130 
#define  CH_IT_MAC 129 
#define  CH_IT_NVR 128 
 void* CH_STAT_INVALID ; 
 void* CH_STAT_PENDING ; 
 scalar_t__ CODE_TYPE_EFI ; 
 scalar_t__ CODE_TYPE_OPEN ; 
 scalar_t__ CODE_TYPE_PC ; 
 scalar_t__ FI_AT_UNKNWN ; 
 void* FI_STAT_ADAPTYP ; 
 void* FI_STAT_CHKSUM ; 
 void* FI_STAT_LENGTH ; 
 void* FI_STAT_MISSING ; 
 void* FI_STAT_UNKNOWN ; 
 scalar_t__ calc_fi_checksum (struct esas2r_flash_context*) ; 
 scalar_t__ chk_boot (scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  chk_cfg (scalar_t__*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_fi_adap_type (struct esas2r_adapter*) ; 

__attribute__((used)) static bool verify_fi(struct esas2r_adapter *a,
		      struct esas2r_flash_context *fc)
{
	struct esas2r_flash_img *fi = fc->fi;
	u8 type;
	bool imgerr;
	u16 i;
	u32 len;
	struct esas2r_component_header *ch;

	/* Verify the length - length must even since we do a word checksum */
	len = fi->length;

	if ((len & 1)
	    || len < fc->fi_hdr_len) {
		fi->status = FI_STAT_LENGTH;
		return false;
	}

	/* Get adapter type and verify type in flash image */
	type = get_fi_adap_type(a);
	if ((type == FI_AT_UNKNWN) || (fi->adap_typ != type)) {
		fi->status = FI_STAT_ADAPTYP;
		return false;
	}

	/*
	 * Loop through each component and verify the img_type and length
	 * fields.  Keep a running count of the sizes sooze we can verify total
	 * size to additive size.
	 */
	imgerr = false;

	for (i = 0, len = 0, ch = fi->cmp_hdr;
	     i < fi->num_comps;
	     i++, ch++) {
		bool cmperr = false;

		/*
		 * Verify that the component header has the same index as the
		 * image type.  The headers must be ordered correctly
		 */
		if (i != ch->img_type) {
			imgerr = true;
			ch->status = CH_STAT_INVALID;
			continue;
		}

		switch (ch->img_type) {
		case CH_IT_BIOS:
			type = CODE_TYPE_PC;
			break;

		case CH_IT_MAC:
			type = CODE_TYPE_OPEN;
			break;

		case CH_IT_EFI:
			type = CODE_TYPE_EFI;
			break;
		}

		switch (ch->img_type) {
		case CH_IT_FW:
		case CH_IT_NVR:
			break;

		case CH_IT_BIOS:
		case CH_IT_MAC:
		case CH_IT_EFI:
			if (ch->length & 0x1ff)
				cmperr = true;

			/* Test if component image is present  */
			if (ch->length == 0)
				break;

			/* Image is present - verify the image */
			if (chk_boot((u8 *)fi + ch->image_offset, ch->length)
			    != type)
				cmperr = true;

			break;

		case CH_IT_CFG:

			/* Test if component image is present */
			if (ch->length == 0) {
				cmperr = true;
				break;
			}

			/* Image is present - verify the image */
			if (!chk_cfg((u8 *)fi + ch->image_offset + ch->length,
				     ch->length, NULL))
				cmperr = true;

			break;

		default:

			fi->status = FI_STAT_UNKNOWN;
			return false;
		}

		if (cmperr) {
			imgerr = true;
			ch->status = CH_STAT_INVALID;
		} else {
			ch->status = CH_STAT_PENDING;
			len += ch->length;
		}
	}

	if (imgerr) {
		fi->status = FI_STAT_MISSING;
		return false;
	}

	/* Compare fi->length to the sum of ch->length fields */
	if (len != fi->length - fc->fi_hdr_len) {
		fi->status = FI_STAT_LENGTH;
		return false;
	}

	/* Compute the checksum - it should come out zero */
	if (fi->checksum != calc_fi_checksum(fc)) {
		fi->status = FI_STAT_CHKSUM;
		return false;
	}

	return true;
}