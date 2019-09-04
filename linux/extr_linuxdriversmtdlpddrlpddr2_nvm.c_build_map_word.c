#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/ * x; TYPE_1__ member_0; } ;
typedef  TYPE_2__ map_word ;

/* Variables and functions */

__attribute__((used)) static inline map_word build_map_word(u_long myword)
{
	map_word val = { {0} };
	val.x[0] = myword;
	return val;
}