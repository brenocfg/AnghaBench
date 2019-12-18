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
typedef  int /*<<< orphan*/  u32 ;
struct console_data {scalar_t__ start_addr; scalar_t__ end_of_data; TYPE_1__* hdr; } ;
struct TYPE_2__ {int /*<<< orphan*/  last_byte; } ;

/* Variables and functions */
 scalar_t__ LAST_BYTE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void adjust_end(struct console_data *cd)
{
	u32 last_byte = readl(&cd->hdr->last_byte);

	cd->end_of_data = cd->start_addr + LAST_BYTE(last_byte);
}