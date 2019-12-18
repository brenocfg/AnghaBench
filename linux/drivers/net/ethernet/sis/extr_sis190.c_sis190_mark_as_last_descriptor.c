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
struct RxDesc {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  RingEnd ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sis190_mark_as_last_descriptor(struct RxDesc *desc)
{
	desc->size |= cpu_to_le32(RingEnd);
}