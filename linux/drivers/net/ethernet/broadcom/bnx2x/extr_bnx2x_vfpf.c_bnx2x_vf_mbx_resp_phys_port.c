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
typedef  int u16 ;
struct vfpf_port_phys_id_resp_tlv {int /*<<< orphan*/  id; } ;
struct bnx2x_virtf {int dummy; } ;
struct bnx2x {int flags; int /*<<< orphan*/  phys_port_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_TLV_PHYS_PORT_ID ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int HAS_PHYS_PORT_ID ; 
 int /*<<< orphan*/  bnx2x_add_tlv (struct bnx2x*,void*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_vf_mbx_resp_phys_port(struct bnx2x *bp,
					struct bnx2x_virtf *vf,
					void *buffer,
					u16 *offset)
{
	struct vfpf_port_phys_id_resp_tlv *port_id;

	if (!(bp->flags & HAS_PHYS_PORT_ID))
		return;

	bnx2x_add_tlv(bp, buffer, *offset, CHANNEL_TLV_PHYS_PORT_ID,
		      sizeof(struct vfpf_port_phys_id_resp_tlv));

	port_id = (struct vfpf_port_phys_id_resp_tlv *)
		  (((u8 *)buffer) + *offset);
	memcpy(port_id->id, bp->phys_port_id, ETH_ALEN);

	/* Offset should continue representing the offset to the tail
	 * of TLV data (outside this function scope)
	 */
	*offset += sizeof(struct vfpf_port_phys_id_resp_tlv);
}