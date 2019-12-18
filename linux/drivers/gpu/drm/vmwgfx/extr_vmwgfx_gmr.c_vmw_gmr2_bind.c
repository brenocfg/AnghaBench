#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int uint32_t ;
struct vmw_private {int dummy; } ;
struct vmw_piter {int dummy; } ;
typedef  int /*<<< orphan*/  remap_cmd ;
typedef  int /*<<< orphan*/  define_cmd ;
struct TYPE_4__ {int gmrId; unsigned long numPages; int offsetPages; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ SVGAFifoCmdRemapGMR2 ;
typedef  TYPE_1__ SVGAFifoCmdDefineGMR2 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOMEM ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  SVGA_CMD_DEFINE_GMR2 ; 
 int /*<<< orphan*/  SVGA_CMD_REMAP_GMR2 ; 
 int /*<<< orphan*/  SVGA_REMAP_GMR2_PPN32 ; 
 int /*<<< orphan*/  SVGA_REMAP_GMR2_PPN64 ; 
 int* VMW_FIFO_RESERVE (struct vmw_private*,int) ; 
 unsigned long VMW_PPN_PER_REMAP ; 
 unsigned long VMW_PPN_SIZE ; 
 int /*<<< orphan*/  memcpy (int*,TYPE_1__*,int) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmw_fifo_commit (struct vmw_private*,int) ; 
 int vmw_piter_dma_addr (struct vmw_piter*) ; 
 int /*<<< orphan*/  vmw_piter_next (struct vmw_piter*) ; 

__attribute__((used)) static int vmw_gmr2_bind(struct vmw_private *dev_priv,
			 struct vmw_piter *iter,
			 unsigned long num_pages,
			 int gmr_id)
{
	SVGAFifoCmdDefineGMR2 define_cmd;
	SVGAFifoCmdRemapGMR2 remap_cmd;
	uint32_t *cmd;
	uint32_t *cmd_orig;
	uint32_t define_size = sizeof(define_cmd) + sizeof(*cmd);
	uint32_t remap_num = num_pages / VMW_PPN_PER_REMAP + ((num_pages % VMW_PPN_PER_REMAP) > 0);
	uint32_t remap_size = VMW_PPN_SIZE * num_pages + (sizeof(remap_cmd) + sizeof(*cmd)) * remap_num;
	uint32_t remap_pos = 0;
	uint32_t cmd_size = define_size + remap_size;
	uint32_t i;

	cmd_orig = cmd = VMW_FIFO_RESERVE(dev_priv, cmd_size);
	if (unlikely(cmd == NULL))
		return -ENOMEM;

	define_cmd.gmrId = gmr_id;
	define_cmd.numPages = num_pages;

	*cmd++ = SVGA_CMD_DEFINE_GMR2;
	memcpy(cmd, &define_cmd, sizeof(define_cmd));
	cmd += sizeof(define_cmd) / sizeof(*cmd);

	/*
	 * Need to split the command if there are too many
	 * pages that goes into the gmr.
	 */

	remap_cmd.gmrId = gmr_id;
	remap_cmd.flags = (VMW_PPN_SIZE > sizeof(*cmd)) ?
		SVGA_REMAP_GMR2_PPN64 : SVGA_REMAP_GMR2_PPN32;

	while (num_pages > 0) {
		unsigned long nr = min(num_pages, (unsigned long)VMW_PPN_PER_REMAP);

		remap_cmd.offsetPages = remap_pos;
		remap_cmd.numPages = nr;

		*cmd++ = SVGA_CMD_REMAP_GMR2;
		memcpy(cmd, &remap_cmd, sizeof(remap_cmd));
		cmd += sizeof(remap_cmd) / sizeof(*cmd);

		for (i = 0; i < nr; ++i) {
			if (VMW_PPN_SIZE <= 4)
				*cmd = vmw_piter_dma_addr(iter) >> PAGE_SHIFT;
			else
				*((uint64_t *)cmd) = vmw_piter_dma_addr(iter) >>
					PAGE_SHIFT;

			cmd += VMW_PPN_SIZE / sizeof(*cmd);
			vmw_piter_next(iter);
		}

		num_pages -= nr;
		remap_pos += nr;
	}

	BUG_ON(cmd != cmd_orig + cmd_size / sizeof(*cmd));

	vmw_fifo_commit(dev_priv, cmd_size);

	return 0;
}