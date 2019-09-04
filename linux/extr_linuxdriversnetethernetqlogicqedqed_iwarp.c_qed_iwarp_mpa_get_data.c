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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct unaligned_opaque_data {int /*<<< orphan*/  cid; scalar_t__ first_mpa_offset; scalar_t__ tcp_payload_offset; } ;
struct qed_hwfn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HILO_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qed_iwarp_mpa_get_data(struct qed_hwfn *p_hwfn,
		       struct unaligned_opaque_data *curr_pkt,
		       u32 opaque_data0, u32 opaque_data1)
{
	u64 opaque_data;

	opaque_data = HILO_64(opaque_data1, opaque_data0);
	*curr_pkt = *((struct unaligned_opaque_data *)&opaque_data);

	curr_pkt->first_mpa_offset = curr_pkt->tcp_payload_offset +
				     le16_to_cpu(curr_pkt->first_mpa_offset);
	curr_pkt->cid = le32_to_cpu(curr_pkt->cid);
}