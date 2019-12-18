#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  format; } ;
struct ibmvfc_event {void (* done ) (struct ibmvfc_event*) ;int /*<<< orphan*/ * eh_comp; TYPE_1__ crq; int /*<<< orphan*/ * sync_iu; int /*<<< orphan*/ * cmnd; } ;

/* Variables and functions */

__attribute__((used)) static void ibmvfc_init_event(struct ibmvfc_event *evt,
			      void (*done) (struct ibmvfc_event *), u8 format)
{
	evt->cmnd = NULL;
	evt->sync_iu = NULL;
	evt->crq.format = format;
	evt->done = done;
	evt->eh_comp = NULL;
}