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
struct ide_port_info {int dummy; } ;
typedef  int /*<<< orphan*/  ide_hwif_t ;

/* Variables and functions */
 int EOPNOTSUPP ; 

__attribute__((used)) static int icside_dma_off_init(ide_hwif_t *hwif, const struct ide_port_info *d)
{
	return -EOPNOTSUPP;
}