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
struct efx_rss_context {scalar_t__ context_id; } ;

/* Variables and functions */
 scalar_t__ EFX_EF10_RSS_CONTEXT_INVALID ; 

__attribute__((used)) static inline bool efx_rss_active(struct efx_rss_context *ctx)
{
	return ctx->context_id != EFX_EF10_RSS_CONTEXT_INVALID;
}