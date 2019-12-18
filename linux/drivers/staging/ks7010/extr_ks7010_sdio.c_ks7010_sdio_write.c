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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct sdio_func {int dummy; } ;
struct ks_wlan_private {int dummy; } ;

/* Variables and functions */
 struct sdio_func* ks7010_to_func (struct ks_wlan_private*) ; 
 int sdio_memcpy_toio (struct sdio_func*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static int ks7010_sdio_write(struct ks_wlan_private *priv, u32 address,
			     u8 *buffer, unsigned int length)
{
	struct sdio_func *func = ks7010_to_func(priv);

	return sdio_memcpy_toio(func, address, buffer, length);
}