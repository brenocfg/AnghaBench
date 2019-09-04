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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  size; int /*<<< orphan*/  nsid; } ;
struct vmw_escape_header {TYPE_1__ body; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  SVGA_CMD_ESCAPE ; 
 int /*<<< orphan*/  SVGA_ESCAPE_NSID_VMWARE ; 

__attribute__((used)) static inline void fill_escape(struct vmw_escape_header *header,
			       uint32_t size)
{
	header->cmd = SVGA_CMD_ESCAPE;
	header->body.nsid = SVGA_ESCAPE_NSID_VMWARE;
	header->body.size = size;
}