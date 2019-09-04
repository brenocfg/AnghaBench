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
struct TYPE_2__ {int /*<<< orphan*/  tx_kicks; } ;
struct vector_private {int /*<<< orphan*/  tx_queue; TYPE_1__ estats; } ;

/* Variables and functions */
 int /*<<< orphan*/  vector_send (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vector_tx_poll(unsigned long data)
{
	struct vector_private *vp = (struct vector_private *)data;

	vp->estats.tx_kicks++;
	vector_send(vp->tx_queue);
}