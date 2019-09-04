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
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct bnxt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline struct net_device *bnxt_get_vf_rep(struct bnxt *bp, u16 cfa_code)
{
	return NULL;
}