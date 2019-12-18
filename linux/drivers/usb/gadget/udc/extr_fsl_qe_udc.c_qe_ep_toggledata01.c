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
struct qe_ep {int data01; } ;

/* Variables and functions */

__attribute__((used)) static int qe_ep_toggledata01(struct qe_ep *ep)
{
	ep->data01 ^= 0x1;
	return 0;
}