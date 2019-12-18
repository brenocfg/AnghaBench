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
typedef  int uint8_t ;
struct whc_qset {TYPE_2__* ep; } ;
struct whc {int dummy; } ;
struct TYPE_3__ {int bInterval; } ;
struct TYPE_4__ {TYPE_1__ desc; } ;

/* Variables and functions */

__attribute__((used)) static int qset_get_period(struct whc *whc, struct whc_qset *qset)
{
	uint8_t bInterval = qset->ep->desc.bInterval;

	if (bInterval < 6)
		bInterval = 6;
	if (bInterval > 10)
		bInterval = 10;
	return bInterval - 6;
}