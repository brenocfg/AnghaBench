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
struct ltq_wdt_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ltq_wdt_r32 (struct ltq_wdt_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ltq_wdt_w32 (struct ltq_wdt_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ltq_wdt_mask(struct ltq_wdt_priv *priv, u32 clear, u32 set,
			 u32 offset)
{
	u32 val = ltq_wdt_r32(priv, offset);

	val &= ~(clear);
	val |= set;
	ltq_wdt_w32(priv, val, offset);
}