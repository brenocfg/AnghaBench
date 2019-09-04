#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource_pool {struct clock_source** clock_sources; } ;
struct resource_context {int dummy; } ;
struct dc_stream_state {TYPE_3__* sink; } ;
struct clock_source {int dummy; } ;
struct TYPE_6__ {TYPE_2__* link; } ;
struct TYPE_5__ {TYPE_1__* link_enc; } ;
struct TYPE_4__ {int transmitter; } ;

/* Variables and functions */
 size_t DCE112_CLK_SRC_PLL0 ; 
 size_t DCE112_CLK_SRC_PLL1 ; 
 size_t DCE112_CLK_SRC_PLL2 ; 
 size_t DCE112_CLK_SRC_PLL3 ; 
 size_t DCE112_CLK_SRC_PLL4 ; 
 size_t DCE112_CLK_SRC_PLL5 ; 
#define  TRANSMITTER_UNIPHY_A 133 
#define  TRANSMITTER_UNIPHY_B 132 
#define  TRANSMITTER_UNIPHY_C 131 
#define  TRANSMITTER_UNIPHY_D 130 
#define  TRANSMITTER_UNIPHY_E 129 
#define  TRANSMITTER_UNIPHY_F 128 

__attribute__((used)) static struct clock_source *find_matching_pll(
		struct resource_context *res_ctx,
		const struct resource_pool *pool,
		const struct dc_stream_state *const stream)
{
	switch (stream->sink->link->link_enc->transmitter) {
	case TRANSMITTER_UNIPHY_A:
		return pool->clock_sources[DCE112_CLK_SRC_PLL0];
	case TRANSMITTER_UNIPHY_B:
		return pool->clock_sources[DCE112_CLK_SRC_PLL1];
	case TRANSMITTER_UNIPHY_C:
		return pool->clock_sources[DCE112_CLK_SRC_PLL2];
	case TRANSMITTER_UNIPHY_D:
		return pool->clock_sources[DCE112_CLK_SRC_PLL3];
	case TRANSMITTER_UNIPHY_E:
		return pool->clock_sources[DCE112_CLK_SRC_PLL4];
	case TRANSMITTER_UNIPHY_F:
		return pool->clock_sources[DCE112_CLK_SRC_PLL5];
	default:
		return NULL;
	};

	return 0;
}