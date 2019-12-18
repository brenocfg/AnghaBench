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
struct fm10k_intfc {int dummy; } ;

/* Variables and functions */
 scalar_t__ fm10k_cache_ring_qos (struct fm10k_intfc*) ; 
 int /*<<< orphan*/  fm10k_cache_ring_rss (struct fm10k_intfc*) ; 

__attribute__((used)) static void fm10k_assign_rings(struct fm10k_intfc *interface)
{
	if (fm10k_cache_ring_qos(interface))
		return;

	fm10k_cache_ring_rss(interface);
}