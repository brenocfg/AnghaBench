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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct tb_cfg_result {int /*<<< orphan*/  err; int /*<<< orphan*/  response_route; scalar_t__ response_port; int /*<<< orphan*/  member_0; } ;
struct tb_cfg_header {int dummy; } ;
struct TYPE_2__ {scalar_t__ eof; } ;
struct ctl_pkg {TYPE_1__ frame; struct tb_cfg_header* buffer; } ;
typedef  enum tb_cfg_pkg_type { ____Placeholder_tb_cfg_pkg_type } tb_cfg_pkg_type ;

/* Variables and functions */
 scalar_t__ TB_CFG_PKG_ERROR ; 
 int /*<<< orphan*/  check_header (struct ctl_pkg const*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct tb_cfg_result decode_error (struct ctl_pkg const*) ; 
 int /*<<< orphan*/  tb_cfg_get_route (struct tb_cfg_header*) ; 

__attribute__((used)) static struct tb_cfg_result parse_header(const struct ctl_pkg *pkg, u32 len,
					 enum tb_cfg_pkg_type type, u64 route)
{
	struct tb_cfg_header *header = pkg->buffer;
	struct tb_cfg_result res = { 0 };

	if (pkg->frame.eof == TB_CFG_PKG_ERROR)
		return decode_error(pkg);

	res.response_port = 0; /* will be updated later for cfg_read/write */
	res.response_route = tb_cfg_get_route(header);
	res.err = check_header(pkg, len, type, route);
	return res;
}