#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int filter_flags; } ;
struct il_priv {TYPE_1__ active; } ;

/* Variables and functions */
 int RXON_FILTER_ASSOC_MSK ; 

__attribute__((used)) static inline int
il_is_associated(struct il_priv *il)
{
	return (il->active.filter_flags & RXON_FILTER_ASSOC_MSK) ? 1 : 0;
}