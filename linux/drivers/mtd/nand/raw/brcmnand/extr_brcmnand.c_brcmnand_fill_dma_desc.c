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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  void* u32 ;
struct brcmnand_host {int /*<<< orphan*/  cs; } ;
struct brcm_nand_dma_desc {int cmd_irq; int status_valid; int /*<<< orphan*/  cs; void* flash_addr_ext; void* flash_addr; void* total_len; void* tfr_len; void* dram_addr_ext; void* dram_addr; void* next_desc_ext; void* next_desc; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* lower_32_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct brcm_nand_dma_desc*,int /*<<< orphan*/ ,int) ; 
 void* upper_32_bits (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int brcmnand_fill_dma_desc(struct brcmnand_host *host,
				  struct brcm_nand_dma_desc *desc, u64 addr,
				  dma_addr_t buf, u32 len, u8 dma_cmd,
				  bool begin, bool end,
				  dma_addr_t next_desc)
{
	memset(desc, 0, sizeof(*desc));
	/* Descriptors are written in native byte order (wordwise) */
	desc->next_desc = lower_32_bits(next_desc);
	desc->next_desc_ext = upper_32_bits(next_desc);
	desc->cmd_irq = (dma_cmd << 24) |
		(end ? (0x03 << 8) : 0) | /* IRQ | STOP */
		(!!begin) | ((!!end) << 1); /* head, tail */
#ifdef CONFIG_CPU_BIG_ENDIAN
	desc->cmd_irq |= 0x01 << 12;
#endif
	desc->dram_addr = lower_32_bits(buf);
	desc->dram_addr_ext = upper_32_bits(buf);
	desc->tfr_len = len;
	desc->total_len = len;
	desc->flash_addr = lower_32_bits(addr);
	desc->flash_addr_ext = upper_32_bits(addr);
	desc->cs = host->cs;
	desc->status_valid = 0x01;
	return 0;
}