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
struct i40e_vsi {unsigned int alloc_queue_pairs; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int i40e_max_channels(struct i40e_vsi *vsi)
{
	/* TODO: This code assumes DCB and FD is disabled for now. */
	return vsi->alloc_queue_pairs;
}