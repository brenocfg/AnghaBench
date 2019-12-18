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
typedef  int u32 ;
struct mwifiex_ie_types_header {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  type; } ;
struct mwifiex_ie_types_data {scalar_t__ data; TYPE_1__ header; } ;
struct mwifiex_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INFO ; 
#define  TLV_TYPE_CHANNELBANDLIST 129 
#define  TLV_TYPE_TSFTIMESTAMP 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (struct mwifiex_adapter*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
mwifiex_ret_802_11_scan_get_tlv_ptrs(struct mwifiex_adapter *adapter,
				     struct mwifiex_ie_types_data *tlv,
				     u32 tlv_buf_size, u32 req_tlv_type,
				     struct mwifiex_ie_types_data **tlv_data)
{
	struct mwifiex_ie_types_data *current_tlv;
	u32 tlv_buf_left;
	u32 tlv_type;
	u32 tlv_len;

	current_tlv = tlv;
	tlv_buf_left = tlv_buf_size;
	*tlv_data = NULL;

	mwifiex_dbg(adapter, INFO,
		    "info: SCAN_RESP: tlv_buf_size = %d\n",
		    tlv_buf_size);

	while (tlv_buf_left >= sizeof(struct mwifiex_ie_types_header)) {

		tlv_type = le16_to_cpu(current_tlv->header.type);
		tlv_len = le16_to_cpu(current_tlv->header.len);

		if (sizeof(tlv->header) + tlv_len > tlv_buf_left) {
			mwifiex_dbg(adapter, ERROR,
				    "SCAN_RESP: TLV buffer corrupt\n");
			break;
		}

		if (req_tlv_type == tlv_type) {
			switch (tlv_type) {
			case TLV_TYPE_TSFTIMESTAMP:
				mwifiex_dbg(adapter, INFO,
					    "info: SCAN_RESP: TSF\t"
					    "timestamp TLV, len = %d\n",
					    tlv_len);
				*tlv_data = current_tlv;
				break;
			case TLV_TYPE_CHANNELBANDLIST:
				mwifiex_dbg(adapter, INFO,
					    "info: SCAN_RESP: channel\t"
					    "band list TLV, len = %d\n",
					    tlv_len);
				*tlv_data = current_tlv;
				break;
			default:
				mwifiex_dbg(adapter, ERROR,
					    "SCAN_RESP: unhandled TLV = %d\n",
					    tlv_type);
				/* Give up, this seems corrupted */
				return;
			}
		}

		if (*tlv_data)
			break;


		tlv_buf_left -= (sizeof(tlv->header) + tlv_len);
		current_tlv =
			(struct mwifiex_ie_types_data *) (current_tlv->data +
							  tlv_len);

	}			/* while */
}