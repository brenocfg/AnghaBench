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
struct fotg210_udc {scalar_t__ reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISGR0_CX_COMABT_INT ; 
 scalar_t__ FOTG210_DISGR0 ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void fotg210_clear_comabt_int(struct fotg210_udc *fotg210)
{
	u32 value = ioread32(fotg210->reg + FOTG210_DISGR0);

	value &= ~DISGR0_CX_COMABT_INT;
	iowrite32(value, fotg210->reg + FOTG210_DISGR0);
}