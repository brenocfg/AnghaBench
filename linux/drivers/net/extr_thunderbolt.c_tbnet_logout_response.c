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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct thunderbolt_ip_status {int /*<<< orphan*/  hdr; } ;
struct tbnet {int /*<<< orphan*/  command_id; struct tb_xdomain* xd; } ;
struct tb_xdomain {int /*<<< orphan*/  remote_uuid; int /*<<< orphan*/  local_uuid; } ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  TBIP_STATUS ; 
 int /*<<< orphan*/  TB_CFG_PKG_XDOMAIN_RESP ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct thunderbolt_ip_status*,int /*<<< orphan*/ ,int) ; 
 int tb_xdomain_response (struct tb_xdomain*,struct thunderbolt_ip_status*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbnet_fill_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tbnet_logout_response(struct tbnet *net, u64 route, u8 sequence,
				 u32 command_id)
{
	struct thunderbolt_ip_status reply;
	struct tb_xdomain *xd = net->xd;

	memset(&reply, 0, sizeof(reply));
	tbnet_fill_header(&reply.hdr, route, sequence, xd->local_uuid,
			  xd->remote_uuid, TBIP_STATUS, sizeof(reply),
			  atomic_inc_return(&net->command_id));
	return tb_xdomain_response(xd, &reply, sizeof(reply),
				   TB_CFG_PKG_XDOMAIN_RESP);
}