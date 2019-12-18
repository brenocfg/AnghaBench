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
struct btt_sb {int dummy; } ;
struct arena_info {int /*<<< orphan*/  infooff; } ;

/* Variables and functions */
 int arena_read_bytes (struct arena_info*,int /*<<< orphan*/ ,struct btt_sb*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btt_info_read(struct arena_info *arena, struct btt_sb *super)
{
	return arena_read_bytes(arena, arena->infooff, super,
			sizeof(struct btt_sb), 0);
}