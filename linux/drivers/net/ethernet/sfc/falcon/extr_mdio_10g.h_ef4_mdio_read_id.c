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
typedef  int u16 ;
struct ef4_nic {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_DEVID1 ; 
 int /*<<< orphan*/  MDIO_DEVID2 ; 
 int ef4_mdio_read (struct ef4_nic*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 ef4_mdio_read_id(struct ef4_nic *efx, int mmd)
{
	u16 id_low = ef4_mdio_read(efx, mmd, MDIO_DEVID2);
	u16 id_hi = ef4_mdio_read(efx, mmd, MDIO_DEVID1);
	return (id_hi << 16) | (id_low);
}