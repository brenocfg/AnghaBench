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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  MDP4_OVERLAY_FLUSH_OVLP0 ; 
 int /*<<< orphan*/  MDP4_OVERLAY_FLUSH_OVLP1 ; 

__attribute__((used)) static inline uint32_t ovlp2flush(int ovlp)
{
	switch (ovlp) {
	case 0:        return MDP4_OVERLAY_FLUSH_OVLP0;
	case 1:        return MDP4_OVERLAY_FLUSH_OVLP1;
	default:       return 0;
	}
}