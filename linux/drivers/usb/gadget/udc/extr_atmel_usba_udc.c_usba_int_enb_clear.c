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
struct usba_udc {int int_enb_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_ENB ; 
 int /*<<< orphan*/  usba_writel (struct usba_udc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void usba_int_enb_clear(struct usba_udc *udc, u32 mask)
{
	u32 val;

	val = udc->int_enb_cache & ~mask;
	usba_writel(udc, INT_ENB, val);
	udc->int_enb_cache = val;
}