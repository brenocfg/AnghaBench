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
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct bcm_qspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSPI ; 
 scalar_t__ MSPI_TXRAM ; 
 int /*<<< orphan*/  bcm_qspi_write (struct bcm_qspi*,int /*<<< orphan*/ ,scalar_t__,int) ; 

__attribute__((used)) static inline void write_txram_slot_u16(struct bcm_qspi *qspi, int slot,
					u16 val)
{
	u32 reg_offset = MSPI_TXRAM;
	u32 msb_offset = reg_offset + (slot << 3);
	u32 lsb_offset = reg_offset + (slot << 3) + 0x4;

	bcm_qspi_write(qspi, MSPI, msb_offset, (val >> 8));
	bcm_qspi_write(qspi, MSPI, lsb_offset, (val & 0xff));
}