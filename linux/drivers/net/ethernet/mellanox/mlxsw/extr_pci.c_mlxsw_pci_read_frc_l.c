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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct mlxsw_pci {int /*<<< orphan*/  free_running_clock_offset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE_RUNNING_CLOCK_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlxsw_pci_read32 (struct mlxsw_pci*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mlxsw_pci_read_frc_l(void *bus_priv)
{
	struct mlxsw_pci *mlxsw_pci = bus_priv;
	u64 frc_offset;

	frc_offset = mlxsw_pci->free_running_clock_offset;
	return mlxsw_pci_read32(mlxsw_pci, FREE_RUNNING_CLOCK_L(frc_offset));
}