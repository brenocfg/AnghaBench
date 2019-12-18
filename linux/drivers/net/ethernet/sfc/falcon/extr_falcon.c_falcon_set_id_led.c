#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ef4_nic {int dummy; } ;
typedef  enum ef4_led_mode { ____Placeholder_ef4_led_mode } ef4_led_mode ;
struct TYPE_4__ {TYPE_1__* type; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* set_id_led ) (struct ef4_nic*,int) ;} ;

/* Variables and functions */
 TYPE_2__* falcon_board (struct ef4_nic*) ; 
 int /*<<< orphan*/  stub1 (struct ef4_nic*,int) ; 

__attribute__((used)) static void falcon_set_id_led(struct ef4_nic *efx, enum ef4_led_mode mode)
{
	falcon_board(efx)->type->set_id_led(efx, mode);
}