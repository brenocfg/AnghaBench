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
struct intel_uncore {int flags; } ;

/* Variables and functions */
 int UNCORE_HAS_FIFO ; 

__attribute__((used)) static inline bool
intel_uncore_has_fifo(const struct intel_uncore *uncore)
{
	return uncore->flags & UNCORE_HAS_FIFO;
}