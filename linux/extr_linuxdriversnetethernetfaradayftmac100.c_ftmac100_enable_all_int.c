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
struct ftmac100 {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ FTMAC100_OFFSET_IMR ; 
 int /*<<< orphan*/  INT_MASK_ALL_ENABLED ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ftmac100_enable_all_int(struct ftmac100 *priv)
{
	iowrite32(INT_MASK_ALL_ENABLED, priv->base + FTMAC100_OFFSET_IMR);
}