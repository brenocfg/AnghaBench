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
struct ath10k {int dummy; } ;
typedef  enum ath10k_debug_mask { ____Placeholder_ath10k_debug_mask } ath10k_debug_mask ;

/* Variables and functions */

__attribute__((used)) static inline void ath10k_dbg_dump(struct ath10k *ar,
				   enum ath10k_debug_mask mask,
				   const char *msg, const char *prefix,
				   const void *buf, size_t len)
{
}