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
struct ubi_volume {int reserved_pebs; } ;

/* Variables and functions */

__attribute__((used)) static inline bool ubi_leb_valid(struct ubi_volume *vol, int lnum)
{
	return lnum >= 0 && lnum < vol->reserved_pebs;
}