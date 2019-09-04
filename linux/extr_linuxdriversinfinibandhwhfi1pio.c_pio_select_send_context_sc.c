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
struct send_context {int dummy; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 struct send_context* pio_select_send_context_vl (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sc_to_vlt (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 

struct send_context *pio_select_send_context_sc(struct hfi1_devdata *dd,
						u32 selector, u8 sc5)
{
	u8 vl = sc_to_vlt(dd, sc5);

	return pio_select_send_context_vl(dd, selector, vl);
}