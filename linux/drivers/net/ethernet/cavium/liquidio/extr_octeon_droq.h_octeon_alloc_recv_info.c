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
struct octeon_recv_pkt {int dummy; } ;
struct octeon_recv_info {int /*<<< orphan*/ * rsvd; struct octeon_recv_pkt* recv_pkt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int OCT_RECV_INFO_SIZE ; 
 int OCT_RECV_PKT_SIZE ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct octeon_recv_info *octeon_alloc_recv_info(int extra_bytes)
{
	struct octeon_recv_info *recv_info;
	u8 *buf;

	buf = kmalloc(OCT_RECV_PKT_SIZE + OCT_RECV_INFO_SIZE +
		      extra_bytes, GFP_ATOMIC);
	if (!buf)
		return NULL;

	recv_info = (struct octeon_recv_info *)buf;
	recv_info->recv_pkt =
		(struct octeon_recv_pkt *)(buf + OCT_RECV_INFO_SIZE);
	recv_info->rsvd = NULL;
	if (extra_bytes)
		recv_info->rsvd = buf + OCT_RECV_INFO_SIZE + OCT_RECV_PKT_SIZE;

	return recv_info;
}