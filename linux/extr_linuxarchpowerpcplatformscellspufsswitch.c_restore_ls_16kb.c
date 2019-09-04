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
struct spu_state {TYPE_1__* lscsa; } ;
struct spu {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ls; } ;

/* Variables and functions */
 unsigned int MFC_GET_CMD ; 
 int /*<<< orphan*/  send_mfc_dma (struct spu*,unsigned long,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static inline void restore_ls_16kb(struct spu_state *csa, struct spu *spu)
{
	unsigned long addr = (unsigned long)&csa->lscsa->ls[0];
	unsigned int ls_offset = 0x0;
	unsigned int size = 16384;
	unsigned int tag = 0;
	unsigned int rclass = 0;
	unsigned int cmd = MFC_GET_CMD;

	/* Restore, Step 44:
	 *     Issue a DMA command to restore the first
	 *     16kb of local storage from CSA.
	 */
	send_mfc_dma(spu, addr, ls_offset, size, tag, rclass, cmd);
}