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
typedef  int u64 ;
typedef  scalar_t__ u32 ;
struct tb_cfg_header {int unknown; } ;
struct TYPE_2__ {scalar_t__ size; int eof; int /*<<< orphan*/  sof; } ;
struct ctl_pkg {TYPE_1__ frame; struct tb_cfg_header* buffer; } ;
typedef  enum tb_cfg_pkg_type { ____Placeholder_tb_cfg_pkg_type } tb_cfg_pkg_type ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ WARN (int,char*,int,...) ; 
 int tb_cfg_get_route (struct tb_cfg_header*) ; 

__attribute__((used)) static int check_header(const struct ctl_pkg *pkg, u32 len,
			enum tb_cfg_pkg_type type, u64 route)
{
	struct tb_cfg_header *header = pkg->buffer;

	/* check frame, TODO: frame flags */
	if (WARN(len != pkg->frame.size,
			"wrong framesize (expected %#x, got %#x)\n",
			len, pkg->frame.size))
		return -EIO;
	if (WARN(type != pkg->frame.eof, "wrong eof (expected %#x, got %#x)\n",
			type, pkg->frame.eof))
		return -EIO;
	if (WARN(pkg->frame.sof, "wrong sof (expected 0x0, got %#x)\n",
			pkg->frame.sof))
		return -EIO;

	/* check header */
	if (WARN(header->unknown != 1 << 9,
			"header->unknown is %#x\n", header->unknown))
		return -EIO;
	if (WARN(route != tb_cfg_get_route(header),
			"wrong route (expected %llx, got %llx)",
			route, tb_cfg_get_route(header)))
		return -EIO;
	return 0;
}