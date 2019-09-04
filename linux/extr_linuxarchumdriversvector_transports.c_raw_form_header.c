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
typedef  int /*<<< orphan*/  uint8_t ;
struct virtio_net_hdr {int dummy; } ;
struct vector_private {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  virtio_legacy_is_little_endian () ; 
 int /*<<< orphan*/  virtio_net_hdr_from_skb (struct sk_buff*,struct virtio_net_hdr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int raw_form_header(uint8_t *header,
		struct sk_buff *skb, struct vector_private *vp)
{
	struct virtio_net_hdr *vheader = (struct virtio_net_hdr *) header;

	virtio_net_hdr_from_skb(
		skb,
		vheader,
		virtio_legacy_is_little_endian(),
		false,
		0
	);

	return 0;
}