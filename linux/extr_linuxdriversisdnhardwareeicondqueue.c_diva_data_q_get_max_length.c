#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int max_length; } ;
typedef  TYPE_1__ diva_um_idi_data_queue_t ;

/* Variables and functions */

int diva_data_q_get_max_length(const diva_um_idi_data_queue_t *q)
{
	return (q->max_length);
}