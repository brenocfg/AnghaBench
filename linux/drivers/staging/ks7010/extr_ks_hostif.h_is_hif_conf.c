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
 unsigned short HIF_EVENT_MASK ; 
 int /*<<< orphan*/  is_hif_ind (unsigned short) ; 

__attribute__((used)) static inline bool is_hif_conf(unsigned short event)
{
	return (((event & HIF_EVENT_MASK) == HIF_EVENT_MASK) &&
		((event & ~HIF_EVENT_MASK) > 0x0000) &&
		((event & ~HIF_EVENT_MASK) < 0x0012) &&
		!is_hif_ind(event));
}