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
typedef  int u32 ;
struct img_spfi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPFI_INTERRUPT_CLEAR ; 
 int SPFI_INTERRUPT_GDEX32BIT ; 
 int /*<<< orphan*/  SPFI_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  SPFI_RX_32BIT_VALID_DATA ; 
 int spfi_readl (struct img_spfi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spfi_writel (struct img_spfi*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int spfi_pio_read32(struct img_spfi *spfi, u32 *buf,
				    unsigned int max)
{
	unsigned int count = 0;
	u32 status;

	while (count < max / 4) {
		spfi_writel(spfi, SPFI_INTERRUPT_GDEX32BIT,
			    SPFI_INTERRUPT_CLEAR);
		status = spfi_readl(spfi, SPFI_INTERRUPT_STATUS);
		if (!(status & SPFI_INTERRUPT_GDEX32BIT))
			break;
		buf[count] = spfi_readl(spfi, SPFI_RX_32BIT_VALID_DATA);
		count++;
	}

	return count * 4;
}