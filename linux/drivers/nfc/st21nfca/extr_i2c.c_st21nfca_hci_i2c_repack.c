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
typedef  int u8 ;
struct sk_buff {int len; int* data; } ;

/* Variables and functions */
 int EBADMSG ; 
 int ST21NFCA_BYTE_STUFFING_MASK ; 
 scalar_t__ ST21NFCA_ESCAPE_BYTE_STUFFING ; 
 int check_crc (int*,int) ; 
 int get_frame_size (int*,int) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,int) ; 

__attribute__((used)) static int st21nfca_hci_i2c_repack(struct sk_buff *skb)
{
	int i, j, r, size;

	if (skb->len < 1 || (skb->len > 1 && skb->data[1] != 0))
		return -EBADMSG;

	size = get_frame_size(skb->data, skb->len);
	if (size > 0) {
		skb_trim(skb, size);
		/* remove ST21NFCA byte stuffing for upper layer */
		for (i = 1, j = 0; i < skb->len; i++) {
			if (skb->data[i + j] ==
					(u8) ST21NFCA_ESCAPE_BYTE_STUFFING) {
				skb->data[i] = skb->data[i + j + 1]
						| ST21NFCA_BYTE_STUFFING_MASK;
				i++;
				j++;
			}
			skb->data[i] = skb->data[i + j];
		}
		/* remove byte stuffing useless byte */
		skb_trim(skb, i - j);
		/* remove ST21NFCA_SOF_EOF from head */
		skb_pull(skb, 1);

		r = check_crc(skb->data, skb->len);
		if (r != 0) {
			i = 0;
			return -EBADMSG;
		}

		/* remove headbyte */
		skb_pull(skb, 1);
		/* remove crc. Byte Stuffing is already removed here */
		skb_trim(skb, skb->len - 2);
		return skb->len;
	}
	return 0;
}