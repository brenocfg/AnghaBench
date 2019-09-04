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
struct fm10k_mbx_info {int mbx_hdr; int mbx_reg; int mbmem_reg; int mbmem_len; int /*<<< orphan*/  mbx_lock; } ;
struct fm10k_hw {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_MBX_ACK ; 
 int FM10K_MBX_ACK_INTERRUPT ; 
 int /*<<< orphan*/  FM10K_MBX_ERR_BUSY ; 
 int FM10K_MBX_REQ_INTERRUPT ; 
 int fm10k_read_reg (struct fm10k_hw*,int) ; 
 int /*<<< orphan*/  fm10k_write_reg (struct fm10k_hw*,int,int) ; 

__attribute__((used)) static s32 fm10k_mbx_read(struct fm10k_hw *hw, struct fm10k_mbx_info *mbx)
{
	/* only allow one reader in here at a time */
	if (mbx->mbx_hdr)
		return FM10K_MBX_ERR_BUSY;

	/* read to capture initial interrupt bits */
	if (fm10k_read_reg(hw, mbx->mbx_reg) & FM10K_MBX_REQ_INTERRUPT)
		mbx->mbx_lock = FM10K_MBX_ACK;

	/* write back interrupt bits to clear */
	fm10k_write_reg(hw, mbx->mbx_reg,
			FM10K_MBX_REQ_INTERRUPT | FM10K_MBX_ACK_INTERRUPT);

	/* read remote header */
	mbx->mbx_hdr = fm10k_read_reg(hw, mbx->mbmem_reg ^ mbx->mbmem_len);

	return 0;
}