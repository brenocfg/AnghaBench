#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_4__ {int /*<<< orphan*/  release; int /*<<< orphan*/  acquire; } ;
struct e1000_nvm_info {int opcode_bits; int delay_usec; int override; int page_size; int address_bits; int word_size; TYPE_2__ ops; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int type; } ;
struct e1000_hw {TYPE_1__ mac; struct e1000_nvm_info nvm; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int BIT (int) ; 
 int E1000_EECD_ADDR_BITS ; 
 int E1000_EECD_AUPDEN ; 
 int E1000_EECD_SIZE_EX_MASK ; 
 int E1000_EECD_SIZE_EX_SHIFT ; 
 int /*<<< orphan*/  EECD ; 
 int NVM_WORD_SIZE_BASE_SHIFT ; 
#define  e1000_82573 132 
#define  e1000_82574 131 
#define  e1000_82583 130 
 int /*<<< orphan*/  e1000_get_hw_semaphore_82574 ; 
 int /*<<< orphan*/  e1000_nvm_eeprom_spi ; 
 int /*<<< orphan*/  e1000_nvm_flash_hw ; 
#define  e1000_nvm_override_spi_large 129 
#define  e1000_nvm_override_spi_small 128 
 int /*<<< orphan*/  e1000_put_hw_semaphore_82574 ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ew32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static s32 e1000_init_nvm_params_82571(struct e1000_hw *hw)
{
	struct e1000_nvm_info *nvm = &hw->nvm;
	u32 eecd = er32(EECD);
	u16 size;

	nvm->opcode_bits = 8;
	nvm->delay_usec = 1;
	switch (nvm->override) {
	case e1000_nvm_override_spi_large:
		nvm->page_size = 32;
		nvm->address_bits = 16;
		break;
	case e1000_nvm_override_spi_small:
		nvm->page_size = 8;
		nvm->address_bits = 8;
		break;
	default:
		nvm->page_size = eecd & E1000_EECD_ADDR_BITS ? 32 : 8;
		nvm->address_bits = eecd & E1000_EECD_ADDR_BITS ? 16 : 8;
		break;
	}

	switch (hw->mac.type) {
	case e1000_82573:
	case e1000_82574:
	case e1000_82583:
		if (((eecd >> 15) & 0x3) == 0x3) {
			nvm->type = e1000_nvm_flash_hw;
			nvm->word_size = 2048;
			/* Autonomous Flash update bit must be cleared due
			 * to Flash update issue.
			 */
			eecd &= ~E1000_EECD_AUPDEN;
			ew32(EECD, eecd);
			break;
		}
		/* Fall Through */
	default:
		nvm->type = e1000_nvm_eeprom_spi;
		size = (u16)((eecd & E1000_EECD_SIZE_EX_MASK) >>
			     E1000_EECD_SIZE_EX_SHIFT);
		/* Added to a constant, "size" becomes the left-shift value
		 * for setting word_size.
		 */
		size += NVM_WORD_SIZE_BASE_SHIFT;

		/* EEPROM access above 16k is unsupported */
		if (size > 14)
			size = 14;
		nvm->word_size = BIT(size);
		break;
	}

	/* Function Pointers */
	switch (hw->mac.type) {
	case e1000_82574:
	case e1000_82583:
		nvm->ops.acquire = e1000_get_hw_semaphore_82574;
		nvm->ops.release = e1000_put_hw_semaphore_82574;
		break;
	default:
		break;
	}

	return 0;
}