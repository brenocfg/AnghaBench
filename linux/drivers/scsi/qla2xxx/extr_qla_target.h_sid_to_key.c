#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_3__ {int domain; int area; int al_pa; } ;
typedef  TYPE_1__ be_id_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t sid_to_key(const be_id_t s_id)
{
	return s_id.domain << 16 |
		s_id.area << 8 |
		s_id.al_pa;
}