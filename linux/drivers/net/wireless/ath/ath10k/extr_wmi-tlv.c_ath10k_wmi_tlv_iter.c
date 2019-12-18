#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct wmi_tlv {int /*<<< orphan*/  len; int /*<<< orphan*/  tag; } ;
struct ath10k {int dummy; } ;
struct TYPE_3__ {size_t min_len; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int EINVAL ; 
 size_t __le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,size_t,int,size_t,...) ; 
 TYPE_1__* wmi_tlv_policies ; 

__attribute__((used)) static int
ath10k_wmi_tlv_iter(struct ath10k *ar, const void *ptr, size_t len,
		    int (*iter)(struct ath10k *ar, u16 tag, u16 len,
				const void *ptr, void *data),
		    void *data)
{
	const void *begin = ptr;
	const struct wmi_tlv *tlv;
	u16 tlv_tag, tlv_len;
	int ret;

	while (len > 0) {
		if (len < sizeof(*tlv)) {
			ath10k_dbg(ar, ATH10K_DBG_WMI,
				   "wmi tlv parse failure at byte %zd (%zu bytes left, %zu expected)\n",
				   ptr - begin, len, sizeof(*tlv));
			return -EINVAL;
		}

		tlv = ptr;
		tlv_tag = __le16_to_cpu(tlv->tag);
		tlv_len = __le16_to_cpu(tlv->len);
		ptr += sizeof(*tlv);
		len -= sizeof(*tlv);

		if (tlv_len > len) {
			ath10k_dbg(ar, ATH10K_DBG_WMI,
				   "wmi tlv parse failure of tag %hhu at byte %zd (%zu bytes left, %hhu expected)\n",
				   tlv_tag, ptr - begin, len, tlv_len);
			return -EINVAL;
		}

		if (tlv_tag < ARRAY_SIZE(wmi_tlv_policies) &&
		    wmi_tlv_policies[tlv_tag].min_len &&
		    wmi_tlv_policies[tlv_tag].min_len > tlv_len) {
			ath10k_dbg(ar, ATH10K_DBG_WMI,
				   "wmi tlv parse failure of tag %hhu at byte %zd (%hhu bytes is less than min length %zu)\n",
				   tlv_tag, ptr - begin, tlv_len,
				   wmi_tlv_policies[tlv_tag].min_len);
			return -EINVAL;
		}

		ret = iter(ar, tlv_tag, tlv_len, ptr, data);
		if (ret)
			return ret;

		ptr += tlv_len;
		len -= tlv_len;
	}

	return 0;
}