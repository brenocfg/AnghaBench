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
typedef  int u32 ;
struct log_group {int dummy; } ;
struct arena_info {scalar_t__ logoff; } ;

/* Variables and functions */
 int LOG_GRP_SIZE ; 
 int arena_read_bytes (struct arena_info*,scalar_t__,struct log_group*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int btt_log_group_read(struct arena_info *arena, u32 lane,
			struct log_group *log)
{
	return arena_read_bytes(arena,
			arena->logoff + (lane * LOG_GRP_SIZE), log,
			LOG_GRP_SIZE, 0);
}