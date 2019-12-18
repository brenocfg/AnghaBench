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
struct il_priv {int dummy; } ;

/* Variables and functions */
 int il_is_ready (struct il_priv*) ; 
 scalar_t__ il_is_rfkill (struct il_priv*) ; 

__attribute__((used)) static inline int
il_is_ready_rf(struct il_priv *il)
{

	if (il_is_rfkill(il))
		return 0;

	return il_is_ready(il);
}