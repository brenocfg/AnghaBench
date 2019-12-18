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
struct thunderbolt_ip_status {int dummy; } ;
struct thunderbolt_ip_logout {int /*<<< orphan*/  hdr; } ;
struct tbnet {int /*<<< orphan*/  command_id; struct tb_xdomain* xd; } ;
struct tb_xdomain {int /*<<< orphan*/  remote_uuid; int /*<<< orphan*/  local_uuid; int /*<<< orphan*/  route; } ;
typedef  int /*<<< orphan*/  request ;
typedef  int /*<<< orphan*/  reply ;

/* Variables and functions */
 int /*<<< orphan*/  TBIP_LOGOUT ; 
 int /*<<< orphan*/  TBNET_LOGOUT_TIMEOUT ; 
 int /*<<< orphan*/  TB_CFG_PKG_XDOMAIN_RESP ; 
 int /*<<< orphan*/  atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct thunderbolt_ip_logout*,int /*<<< orphan*/ ,int) ; 
 int tb_xdomain_request (struct tb_xdomain*,struct thunderbolt_ip_logout*,int,int /*<<< orphan*/ ,struct thunderbolt_ip_status*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tbnet_fill_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tbnet_logout_request(struct tbnet *net)
{
	struct thunderbolt_ip_logout request;
	struct thunderbolt_ip_status reply;
	struct tb_xdomain *xd = net->xd;

	memset(&request, 0, sizeof(request));
	tbnet_fill_header(&request.hdr, xd->route, 0, xd->local_uuid,
			  xd->remote_uuid, TBIP_LOGOUT, sizeof(request),
			  atomic_inc_return(&net->command_id));

	return tb_xdomain_request(xd, &request, sizeof(request),
				  TB_CFG_PKG_XDOMAIN_RESP, &reply,
				  sizeof(reply), TB_CFG_PKG_XDOMAIN_RESP,
				  TBNET_LOGOUT_TIMEOUT);
}