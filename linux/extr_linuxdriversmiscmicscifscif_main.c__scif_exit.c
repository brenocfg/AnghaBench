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

/* Variables and functions */
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scif_destroy_scifdev () ; 
 int /*<<< orphan*/  scif_ports ; 
 int /*<<< orphan*/  unaligned_cache ; 

__attribute__((used)) static void _scif_exit(void)
{
	idr_destroy(&scif_ports);
	kmem_cache_destroy(unaligned_cache);
	scif_destroy_scifdev();
}