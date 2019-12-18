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
struct ace_private {scalar_t__ trace_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_TRACE_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ace_dump_trace(struct ace_private *ap)
{
#if 0
	if (!ap->trace_buf)
		if (!(ap->trace_buf = kmalloc(ACE_TRACE_SIZE, GFP_KERNEL)))
		    return;
#endif
}