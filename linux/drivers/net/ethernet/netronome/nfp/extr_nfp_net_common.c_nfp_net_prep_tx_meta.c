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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  tls_handle ;
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_id; } ;
struct TYPE_4__ {TYPE_1__ port_info; } ;
struct metadata_dst {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ METADATA_HW_PORT_MUX ; 
 int /*<<< orphan*/  NFP_NET_META_CONN_HANDLE ; 
 int /*<<< orphan*/  NFP_NET_META_FIELD_SIZE ; 
 int /*<<< orphan*/  NFP_NET_META_PORTID ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  put_unaligned_be32 (int /*<<< orphan*/ ,unsigned char*) ; 
 int /*<<< orphan*/  skb_cow_head (struct sk_buff*,int) ; 
 struct metadata_dst* skb_metadata_dst (struct sk_buff*) ; 
 unsigned char* skb_push (struct sk_buff*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfp_net_prep_tx_meta(struct sk_buff *skb, u64 tls_handle)
{
	struct metadata_dst *md_dst = skb_metadata_dst(skb);
	unsigned char *data;
	u32 meta_id = 0;
	int md_bytes;

	if (likely(!md_dst && !tls_handle))
		return 0;
	if (unlikely(md_dst && md_dst->type != METADATA_HW_PORT_MUX)) {
		if (!tls_handle)
			return 0;
		md_dst = NULL;
	}

	md_bytes = 4 + !!md_dst * 4 + !!tls_handle * 8;

	if (unlikely(skb_cow_head(skb, md_bytes)))
		return -ENOMEM;

	meta_id = 0;
	data = skb_push(skb, md_bytes) + md_bytes;
	if (md_dst) {
		data -= 4;
		put_unaligned_be32(md_dst->u.port_info.port_id, data);
		meta_id = NFP_NET_META_PORTID;
	}
	if (tls_handle) {
		/* conn handle is opaque, we just use u64 to be able to quickly
		 * compare it to zero
		 */
		data -= 8;
		memcpy(data, &tls_handle, sizeof(tls_handle));
		meta_id <<= NFP_NET_META_FIELD_SIZE;
		meta_id |= NFP_NET_META_CONN_HANDLE;
	}

	data -= 4;
	put_unaligned_be32(meta_id, data);

	return md_bytes;
}