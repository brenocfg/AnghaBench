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
struct tb_xdp_properties_changed_response {int /*<<< orphan*/  hdr; } ;
struct tb_ctl {int dummy; } ;
typedef  int /*<<< orphan*/  res ;

/* Variables and functions */
 int /*<<< orphan*/  PROPERTIES_CHANGED_RESPONSE ; 
 int /*<<< orphan*/  TB_CFG_PKG_XDOMAIN_RESP ; 
 int __tb_xdomain_response (struct tb_ctl*,struct tb_xdp_properties_changed_response*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct tb_xdp_properties_changed_response*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tb_xdp_fill_header (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
tb_xdp_properties_changed_response(struct tb_ctl *ctl, u64 route, u8 sequence)
{
	struct tb_xdp_properties_changed_response res;

	memset(&res, 0, sizeof(res));
	tb_xdp_fill_header(&res.hdr, route, sequence,
			   PROPERTIES_CHANGED_RESPONSE, sizeof(res));
	return __tb_xdomain_response(ctl, &res, sizeof(res),
				     TB_CFG_PKG_XDOMAIN_RESP);
}