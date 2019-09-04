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
typedef  int /*<<< orphan*/  u32 ;
struct ahash_req_ctx {int buff_index; int /*<<< orphan*/ * buf_cnt; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 *cc_next_buf_cnt(struct ahash_req_ctx *state)
{
	return &state->buf_cnt[state->buff_index ^ 1];
}