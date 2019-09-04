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
typedef  int u8 ;
typedef  int u32 ;
struct cmac {int /*<<< orphan*/  adapter; TYPE_1__* instance; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_ING_FFILT_MASK0 ; 
 int /*<<< orphan*/  REG_ING_FFILT_MASK1 ; 
 int /*<<< orphan*/  REG_ING_FFILT_MASK2 ; 
 int /*<<< orphan*/  REG_ING_FFILT_UM_EN ; 
 int /*<<< orphan*/  REG_MAC_HIGH_ADDR (int) ; 
 int /*<<< orphan*/  REG_MAC_LOW_ADDR (int) ; 
 int /*<<< orphan*/  vsc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  vsc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mac_set_address(struct cmac* mac, u8 addr[6])
{
	u32 val;
	int port = mac->instance->index;

	vsc_write(mac->adapter, REG_MAC_LOW_ADDR(port),
		  (addr[3] << 16) | (addr[4] << 8) | addr[5]);
	vsc_write(mac->adapter, REG_MAC_HIGH_ADDR(port),
		  (addr[0] << 16) | (addr[1] << 8) | addr[2]);

	vsc_read(mac->adapter, REG_ING_FFILT_UM_EN, &val);
	val &= ~0xf0000000;
	vsc_write(mac->adapter, REG_ING_FFILT_UM_EN, val | (port << 28));

	vsc_write(mac->adapter, REG_ING_FFILT_MASK0,
		  0xffff0000 | (addr[4] << 8) | addr[5]);
	vsc_write(mac->adapter, REG_ING_FFILT_MASK1,
		  0xffff0000 | (addr[2] << 8) | addr[3]);
	vsc_write(mac->adapter, REG_ING_FFILT_MASK2,
		  0xffff0000 | (addr[0] << 8) | addr[1]);
	return 0;
}