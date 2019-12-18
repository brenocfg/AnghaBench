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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct bmi_segmented_metadata {int /*<<< orphan*/ * data; int /*<<< orphan*/  length; int /*<<< orphan*/  addr; } ;
struct bmi_segmented_file_header {scalar_t__ file_flags; scalar_t__ data; int /*<<< orphan*/  magic_num; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
#define  BMI_SGMTFILE_BDDATA 131 
#define  BMI_SGMTFILE_BEGINADDR 130 
#define  BMI_SGMTFILE_DONE 129 
#define  BMI_SGMTFILE_EXEC 128 
 scalar_t__ BMI_SGMTFILE_MAGIC_NUM ; 
 int EINVAL ; 
 scalar_t__ __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int ath10k_bmi_set_start (struct ath10k*,int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,...) ; 
 int ath10k_hw_diag_segment_download (struct ath10k*,int /*<<< orphan*/  const*,int,int) ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int,...) ; 

int ath10k_hw_diag_fast_download(struct ath10k *ar,
				 u32 address,
				 const void *buffer,
				 u32 length)
{
	const u8 *buf = buffer;
	bool sgmt_end = false;
	u32 base_addr = 0;
	u32 base_len = 0;
	u32 left = 0;
	struct bmi_segmented_file_header *hdr;
	struct bmi_segmented_metadata *metadata;
	int ret = 0;

	if (length < sizeof(*hdr))
		return -EINVAL;

	/* check firmware header. If it has no correct magic number
	 * or it's compressed, returns error.
	 */
	hdr = (struct bmi_segmented_file_header *)buf;
	if (__le32_to_cpu(hdr->magic_num) != BMI_SGMTFILE_MAGIC_NUM) {
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "Not a supported firmware, magic_num:0x%x\n",
			   hdr->magic_num);
		return -EINVAL;
	}

	if (hdr->file_flags != 0) {
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "Not a supported firmware, file_flags:0x%x\n",
			   hdr->file_flags);
		return -EINVAL;
	}

	metadata = (struct bmi_segmented_metadata *)hdr->data;
	left = length - sizeof(*hdr);

	while (left > 0) {
		if (left < sizeof(*metadata)) {
			ath10k_warn(ar, "firmware segment is truncated: %d\n",
				    left);
			ret = -EINVAL;
			break;
		}
		base_addr = __le32_to_cpu(metadata->addr);
		base_len = __le32_to_cpu(metadata->length);
		buf = metadata->data;
		left -= sizeof(*metadata);

		switch (base_len) {
		case BMI_SGMTFILE_BEGINADDR:
			/* base_addr is the start address to run */
			ret = ath10k_bmi_set_start(ar, base_addr);
			base_len = 0;
			break;
		case BMI_SGMTFILE_DONE:
			/* no more segment */
			base_len = 0;
			sgmt_end = true;
			ret = 0;
			break;
		case BMI_SGMTFILE_BDDATA:
		case BMI_SGMTFILE_EXEC:
			ath10k_warn(ar,
				    "firmware has unsupported segment:%d\n",
				    base_len);
			ret = -EINVAL;
			break;
		default:
			if (base_len > left) {
				/* sanity check */
				ath10k_warn(ar,
					    "firmware has invalid segment length, %d > %d\n",
					    base_len, left);
				ret = -EINVAL;
				break;
			}

			ret = ath10k_hw_diag_segment_download(ar,
							      buf,
							      base_addr,
							      base_len);

			if (ret)
				ath10k_warn(ar,
					    "failed to download firmware via diag interface:%d\n",
					    ret);
			break;
		}

		if (ret || sgmt_end)
			break;

		metadata = (struct bmi_segmented_metadata *)(buf + base_len);
		left -= base_len;
	}

	if (ret == 0)
		ath10k_dbg(ar, ATH10K_DBG_BOOT,
			   "boot firmware fast diag download successfully.\n");
	return ret;
}