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
struct TYPE_4__ {scalar_t__ short_data; } ;
struct TYPE_3__ {scalar_t__ short_data; } ;
struct ba_record {int valid; TYPE_2__ start_seq_ctrl; scalar_t__ dialog_token; scalar_t__ timeout_value; TYPE_1__ param_set; } ;

/* Variables and functions */

void ResetBaEntry(struct ba_record *pBA)
{
	pBA->valid			= false;
	pBA->param_set.short_data	= 0;
	pBA->timeout_value		= 0;
	pBA->dialog_token		= 0;
	pBA->start_seq_ctrl.short_data	= 0;
}