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
struct dw_apb_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  APBTMR_N_EOI ; 
 int /*<<< orphan*/  apbt_readl_relaxed (struct dw_apb_timer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void apbt_eoi(struct dw_apb_timer *timer)
{
	apbt_readl_relaxed(timer, APBTMR_N_EOI);
}