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
typedef  int u16 ;
struct ks8842_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TXMIR ; 
 int ks8842_read16 (struct ks8842_adapter*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 ks8842_tx_fifo_space(struct ks8842_adapter *adapter)
{
	return ks8842_read16(adapter, 16, REG_TXMIR) & 0x1fff;
}