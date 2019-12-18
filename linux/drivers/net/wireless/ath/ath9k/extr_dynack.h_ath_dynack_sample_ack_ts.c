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
struct sk_buff {int dummy; } ;
struct ath_hw {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void ath_dynack_sample_ack_ts(struct ath_hw *ah,
					    struct sk_buff *skb, u32 ts) {}