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
struct ks8842_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TXCR ; 
 int /*<<< orphan*/  ks8842_enable_bits (struct ks8842_adapter*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ks8842_enable_tx(struct ks8842_adapter *adapter)
{
	ks8842_enable_bits(adapter, 16, 0x01, REG_TXCR);
}