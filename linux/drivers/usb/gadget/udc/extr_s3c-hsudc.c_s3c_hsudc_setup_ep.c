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
struct TYPE_3__ {int /*<<< orphan*/  ep_list; } ;
struct s3c_hsudc {int /*<<< orphan*/ * ep; TYPE_2__* pd; TYPE_1__ gadget; int /*<<< orphan*/  ep0state; } ;
struct TYPE_4__ {int epnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  s3c_hsudc_initep (struct s3c_hsudc*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void s3c_hsudc_setup_ep(struct s3c_hsudc *hsudc)
{
	int epnum;

	hsudc->ep0state = WAIT_FOR_SETUP;
	INIT_LIST_HEAD(&hsudc->gadget.ep_list);
	for (epnum = 0; epnum < hsudc->pd->epnum; epnum++)
		s3c_hsudc_initep(hsudc, &hsudc->ep[epnum], epnum);
}