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
typedef  int /*<<< orphan*/  u32 ;
struct bcm_qspi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSPI ; 
 scalar_t__ MSPI_CDRAM ; 
 int /*<<< orphan*/  bcm_qspi_read (struct bcm_qspi*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32 read_cdram_slot(struct bcm_qspi *qspi, int slot)
{
	return bcm_qspi_read(qspi, MSPI, MSPI_CDRAM + (slot << 2));
}