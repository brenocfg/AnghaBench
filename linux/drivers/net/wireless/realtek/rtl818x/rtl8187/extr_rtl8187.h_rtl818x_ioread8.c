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
struct rtl8187_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rtl818x_ioread8_idx (struct rtl8187_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u8 rtl818x_ioread8(struct rtl8187_priv *priv, u8 *addr)
{
	return rtl818x_ioread8_idx(priv, addr, 0);
}