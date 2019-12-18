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
struct sk_buff {scalar_t__ cb; } ;
struct mwifiex_dma_mapping {int dummy; } ;
struct mwifiex_cb {int /*<<< orphan*/  dma_mapping; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct mwifiex_dma_mapping*,int) ; 

__attribute__((used)) static inline void mwifiex_store_mapping(struct sk_buff *skb,
					 struct mwifiex_dma_mapping *mapping)
{
	struct mwifiex_cb *cb = (struct mwifiex_cb *)skb->cb;

	memcpy(&cb->dma_mapping, mapping, sizeof(*mapping));
}