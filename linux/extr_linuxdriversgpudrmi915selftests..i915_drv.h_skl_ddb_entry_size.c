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
typedef  scalar_t__ uint16_t ;
struct skl_ddb_entry {scalar_t__ start; scalar_t__ end; } ;

/* Variables and functions */

__attribute__((used)) static inline uint16_t skl_ddb_entry_size(const struct skl_ddb_entry *entry)
{
	return entry->end - entry->start;
}