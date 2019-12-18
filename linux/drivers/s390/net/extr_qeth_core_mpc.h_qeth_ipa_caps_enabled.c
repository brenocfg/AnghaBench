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
struct qeth_ipa_caps {int enabled; } ;

/* Variables and functions */

__attribute__((used)) static inline bool qeth_ipa_caps_enabled(struct qeth_ipa_caps *caps, u32 mask)
{
	return (caps->enabled & mask) == mask;
}