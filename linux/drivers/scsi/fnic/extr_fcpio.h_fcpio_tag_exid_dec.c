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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  ox_id; int /*<<< orphan*/  rx_id; } ;
struct TYPE_4__ {TYPE_1__ ex_id; } ;
struct fcpio_tag {TYPE_2__ u; } ;

/* Variables and functions */

__attribute__((used)) static inline void
fcpio_tag_exid_dec(struct fcpio_tag *tag, u16 *ox_id, u16 *rx_id)
{
	*rx_id = tag->u.ex_id.rx_id;
	*ox_id = tag->u.ex_id.ox_id;
}