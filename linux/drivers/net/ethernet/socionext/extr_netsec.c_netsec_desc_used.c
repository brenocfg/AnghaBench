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
struct netsec_desc_ring {scalar_t__ head; scalar_t__ tail; } ;

/* Variables and functions */
 int DESC_NUM ; 

__attribute__((used)) static int netsec_desc_used(struct netsec_desc_ring *dring)
{
	int used;

	if (dring->head >= dring->tail)
		used = dring->head - dring->tail;
	else
		used = dring->head + DESC_NUM - dring->tail;

	return used;
}