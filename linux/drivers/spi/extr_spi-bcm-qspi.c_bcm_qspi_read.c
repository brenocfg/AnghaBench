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
struct bcm_qspi {scalar_t__* base; int /*<<< orphan*/  big_endian; } ;
typedef  enum base_type { ____Placeholder_base_type } base_type ;

/* Variables and functions */
 int /*<<< orphan*/  bcm_qspi_readl (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline u32 bcm_qspi_read(struct bcm_qspi *qspi, enum base_type type,
				unsigned int offset)
{
	return bcm_qspi_readl(qspi->big_endian, qspi->base[type] + offset);
}